#include "SoundSystem.h"
#include <iostream>

// SDLSoundSystem
//***************



// SDL
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
		m_thread.join(); // Stop thread

		m_soundMap.clear(); // Clear all sound before destroying mixer
		MIX_DestroyMixer(m_mixer);
	}

	void Play(const std::string& soundId, const float volume)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_pendingRequests.push(SoundMessage{ soundId, volume });
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
			m_conditionVar.wait(lock, [this, &stopToken]() {
				return not m_pendingRequests.empty() || stopToken.stop_requested();
				});

			while (not m_pendingRequests.empty())
			{
				SoundMessage message = m_pendingRequests.front();

				// Play sound
				auto& sound = m_soundMap[message.id];
				m_pendingRequests.pop();

				lock.unlock();
				if (not sound->IsLoaded())
					sound->Load();
				sound->SetVolume(message.volume);
				sound->Play();
				lock.lock();
			}
		}
	}
private:
	std::unordered_map<std::string, std::unique_ptr<Sound>> m_soundMap;
	MIX_Mixer* m_mixer;

	std::queue<SoundMessage> m_pendingRequests;
	std::jthread m_thread;
	std::mutex m_mutex{};
	std::condition_variable m_conditionVar{};
};

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

void dae::SDLSoundSystem::RegisterSound(const std::string& id, const std::string& path)
{
	m_impl->RegisterSound(id, path);
}

// LoggingSoundSystem
//***************
dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSys):
	m_realSoundSys{std::move(soundSys)}
{
}

void dae::LoggingSoundSystem::Play(const std::string& soundId, const float volume)
{
	std::cout << "playing " << soundId << " at volume " << volume << std::endl;
	m_realSoundSys->Play(soundId, volume);
}

void dae::LoggingSoundSystem::RegisterSound(const std::string& id, const std::string& path)
{
	m_realSoundSys->RegisterSound(id, path);
}
