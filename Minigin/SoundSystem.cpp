#include "SoundSystem.h"
#include <iostream>


dae::SDLSoundSystem::SDLSoundSystem()
{
	m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	m_soundMap.clear(); // Clear all sound before destroying mixer
	MIX_DestroyMixer(m_mixer);
}

void dae::SDLSoundSystem::Play(int soundId, const float volume)
{
	auto& sound = m_soundMap[soundId];
	if (not sound->IsLoaded())
		sound->Load();
	sound->SetVolume(volume);
	sound->Play();
}

void dae::SDLSoundSystem::RegisterSound(int id, const std::string& path)
{
	m_soundMap[id] = std::make_unique<Sound>(path, m_mixer);
}
