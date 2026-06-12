#include "SoundSystem.h"
#include <iostream>
#include <unordered_map>
#include <queue>
#include <thread>
#include <mutex>
#include <SDL3_mixer/SDL_mixer.h>
#include <memory>
#include <algorithm>
// Null
//***************
void dae::NullSoundSystem::Play(const std::string&, const float)
{}

void dae::NullSoundSystem::Stop(const std::string&)
{}

void dae::NullSoundSystem::Loop(const std::string&, const float)
{
}

void dae::NullSoundSystem::RegisterSound(const std::string&, const std::string&)
{}

// SDLSoundSystem
//***************

// SDL
#ifdef __EMSCRIPTEN__
class dae::SDLSoundSystem::SoundSystemImpl final
{
public:
	void Play(const std::string&, const float)
	{
	}

	void Loop(const std::string&, const float)
	{
	}

	void Stop(const std::string&)
	{
	}

	void RegisterSound(const std::string&, const std::string&)
	{
	}
private:

};
#else
class dae::SDLSoundSystem::SoundSystemImpl final
{
public:
	SoundSystemImpl()
	{
		m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
		m_thread = std::jthread([this](std::stop_token stopToken) {
			ProcessRequests(stopToken);
			});
	}

	~SoundSystemImpl()
	{
		m_thread.request_stop();
		m_conditionVar.notify_all();

		m_soundMap.clear(); // Clear all sound before destroying mixer
		MIX_DestroyMixer(m_mixer);
	}
	SoundSystemImpl(const SoundSystemImpl& other) = delete;
	SoundSystemImpl(SoundSystemImpl&& other) = delete;
	SoundSystemImpl& operator=(const SoundSystemImpl& other) = delete;
	SoundSystemImpl& operator=(SoundSystemImpl&& other) = delete;

	void Play(const std::string& soundId, const float volume)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_pendingRequests.push(SoundMessage{ soundId, "Play", volume });
		m_conditionVar.notify_one();
	}

	void Loop(const std::string& soundId, const float volume)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_pendingRequests.push(SoundMessage{ soundId, "Loop", volume });
		m_conditionVar.notify_one();
	}

	void Stop(const std::string& soundId)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_pendingRequests.push(SoundMessage{ soundId, "Stop", 0});
		m_conditionVar.notify_one();
	}

	void RegisterSound(const std::string& id, const std::string& path)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_soundMap[id] = std::make_shared<Sound>(path);
	}

	void ProcessRequests(std::stop_token stopToken)
	{
		while (not stopToken.stop_requested())
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_conditionVar.wait(lock, [this, &stopToken] {
				return stopToken.stop_requested() || !m_pendingRequests.empty();
				});

			while (not m_pendingRequests.empty())
			{
				SoundMessage message = m_pendingRequests.front();
				m_pendingRequests.pop();
				if (not m_soundMap.contains(message.id)) continue;

				// Play sound
				std::shared_ptr<Sound> sound = m_soundMap[message.id];


				lock.unlock();
				if (message.type == "Play")
				{
					if (not IsLoaded(*sound))
						Load(*sound);
					SetVolume(*sound, message.volume);
					PlaySound(*sound, false);
				}
				else if (message.type == "Stop")
				{
					StopSound(*sound);
				}
				else if (message.type == "Loop")
				{
					if (not IsLoaded(*sound))
						Load(*sound);
					SetVolume(*sound, message.volume);
					PlaySound(*sound, true);
				}
				
				lock.lock();
			}
		}
	}
private:
	struct Sound
	{
		explicit Sound(const std::string& _filepath):
			filepath{_filepath}
		{ }

		MIX_Audio* audio{};
		std::vector<MIX_Track*> tracks{};
		std::string filepath;
	};

	MIX_Mixer* m_mixer{};
	std::jthread m_thread;
	std::mutex m_mutex;
	std::condition_variable m_conditionVar;
	std::queue<SoundMessage> m_pendingRequests;
	std::unordered_map<std::string, std::shared_ptr<Sound>> m_soundMap;

	void PlaySound(Sound& sound, bool isLooping)
	{
		for (auto& track : sound.tracks)
		{
			if (not MIX_TrackPlaying(track))
			{
				MIX_SetTrackAudio(track, sound.audio);
				SDL_PropertiesID props{ SDL_CreateProperties() };
				if (isLooping)
				{
					SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, 50);
				}
				MIX_PlayTrack(track, props);
				SDL_DestroyProperties(props);
				return;
			}
		}
			
		// No free tracks found so create a new one
		MIX_Track* newTrack = MIX_CreateTrack(m_mixer);
		MIX_SetTrackAudio(newTrack, sound.audio);
		SDL_PropertiesID props{ SDL_CreateProperties() };
		if (isLooping)
		{
			SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, 50);
		}
		MIX_PlayTrack(newTrack, props);
		sound.tracks.push_back(newTrack);
	}

	void StopSound(const Sound& sound)
	{
		for (const auto& track : sound.tracks)
		{
			if (MIX_TrackPlaying(track))
				MIX_StopTrack(track, 0);
		}
	}

	bool IsLoaded(const Sound& sound)
	{
		return sound.audio != nullptr;
	}

	void Load(Sound& sound)
	{
		sound.audio = MIX_LoadAudio(m_mixer, sound.filepath.c_str(), false);
		sound.tracks.push_back(MIX_CreateTrack(m_mixer));
	}

	void SetVolume(Sound& sound, float volume)
	{
		volume = std::clamp(volume, 0.f, 1.f);
		for (auto& track : sound.tracks)
			MIX_SetTrackGain(track, volume);
	}
};
#endif

// Shared
dae::SDLSoundSystem::SDLSoundSystem():
	m_impl{std::make_unique<SoundSystemImpl>()}
{
}

dae::SDLSoundSystem::~SDLSoundSystem() = default;

void dae::SDLSoundSystem::Play(const std::string& soundId, const float volume)
{
	m_impl->Play(soundId, volume);
}

void dae::SDLSoundSystem::Stop(const std::string& soundId)
{
	m_impl->Stop(soundId);
}

void dae::SDLSoundSystem::Loop(const std::string& soundId, const float volume)
{
	m_impl->Loop(soundId, volume);
}

void dae::SDLSoundSystem::RegisterSound(const std::string& id, const std::string& path)
{
	m_impl->RegisterSound(id, path);
}

// LoggingSoundSystem
//***************
dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<ISoundSystem>&& soundSys):
	m_realSoundSys{std::move(soundSys)}
{
}

void dae::LoggingSoundSystem::Play(const std::string& soundId, const float volume)
{
	std::cout << "playing " << soundId << " at volume " << volume << "\n";
	m_realSoundSys->Play(soundId, volume);
}

void dae::LoggingSoundSystem::Loop(const std::string& soundId, const float volume)
{
	std::cout << "looping " << soundId << " at volume " << volume << "\n";
	m_realSoundSys->Loop(soundId, volume);
}

void dae::LoggingSoundSystem::Stop(const std::string& soundId)
{
	std::cout << "stopped " << soundId << "\n";
	m_realSoundSys->Stop(soundId);
}

void dae::LoggingSoundSystem::RegisterSound(const std::string& id, const std::string& path)
{
	m_realSoundSys->RegisterSound(id, path);
}
