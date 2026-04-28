#include "SoundSystem.h"
#include <iostream>

// SDLSoundSystem
//***************
dae::SDLSoundSystem::SDLSoundSystem()
{
	m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
	m_thread = std::jthread(&SDLSoundSystem::ProcessRequests, this);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	m_isRunning = false;
	m_conditionVar.notify_all();
	m_thread.join(); // Stop thread

	m_soundMap.clear(); // Clear all sound before destroying mixer
	MIX_DestroyMixer(m_mixer);
}

void dae::SDLSoundSystem::Play(const std::string& soundId, const float volume)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_pendingRequests.push(SoundMessage{ soundId, volume });
	m_conditionVar.notify_one();
}

void dae::SDLSoundSystem::RegisterSound(const std::string& id, const std::string& path)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_soundMap[id] = std::make_unique<Sound>(path, m_mixer);
}

void dae::SDLSoundSystem::ProcessRequests()
{
	while (m_isRunning) // As long as this system is running, we don't want to destroy the sound thread
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_conditionVar.wait(lock, [this]() {
			return not m_pendingRequests.empty() || not m_isRunning;
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
