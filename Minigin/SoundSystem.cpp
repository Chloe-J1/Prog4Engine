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

	void Stop(const std::string& soundId)
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
		m_soundMap[id] = std::make_unique<Sound>(path, m_mixer);
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

				// Play sound
				auto& sound = m_soundMap.at(message.id);

				m_pendingRequests.pop();
				if (not m_soundMap.contains(message.id)) continue;

				lock.unlock();
				if (message.type == "Play")
				{
					if (not sound->IsLoaded())
						sound->Load();
					sound->SetVolume(message.volume);
					sound->Play(false);
				}
				else if (message.type == "Stop")
				{
					sound->Stop();
				}
				else if (message.type == "Loop")
				{
					if (not sound->IsLoaded())
						sound->Load();
					sound->SetVolume(message.volume);
					sound->Play(true);
				}
				
				lock.lock();
			}
		}
	}
private:

	class Sound {
	public:
		Sound(const std::string& path, MIX_Mixer* mixer)
			: m_mixer(mixer), m_filepath(path)
		{
		}

		~Sound()
		{
			for (const auto& track : m_tracks)
			{
				MIX_StopTrack(track, 0);
				MIX_DestroyTrack(track);
			}
			MIX_DestroyAudio(m_audio);
		}

		bool IsLoaded() const { return m_audio != nullptr; }

		void Load()
		{
			m_audio = MIX_LoadAudio(m_mixer, m_filepath.c_str(), false);
			m_tracks.push_back(MIX_CreateTrack(m_mixer));
		}

		void SetVolume(float volume)
		{
			volume = std::clamp(volume, 0.f, 1.f);
			for (auto& track : m_tracks)
				MIX_SetTrackGain(track, volume);
		}

		void Play(bool isLooping)
		{
			for (auto& track : m_tracks)
			{
				if (not MIX_TrackPlaying(track))
				{
					MIX_SetTrackAudio(track, m_audio);
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
			MIX_SetTrackAudio(newTrack, m_audio);
			SDL_PropertiesID props{ SDL_CreateProperties() };
			if (isLooping)
			{
				SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, 50);
			}
			MIX_PlayTrack(newTrack, props);
			m_tracks.push_back(newTrack);
		}

		void Stop()
		{
			for (const auto& track : m_tracks)
			{
				if (MIX_TrackPlaying(track))
					MIX_StopTrack(track, 0);
			}
		}

	private:
		MIX_Mixer* m_mixer;
		MIX_Audio* m_audio{};
		std::vector<MIX_Track*> m_tracks{};
		std::string m_filepath;
	};

	MIX_Mixer* m_mixer{};
	std::jthread m_thread;
	std::mutex m_mutex;
	std::condition_variable m_conditionVar;
	std::queue<SoundMessage> m_pendingRequests;
	std::unordered_map<std::string, std::unique_ptr<Sound>> m_soundMap;
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
