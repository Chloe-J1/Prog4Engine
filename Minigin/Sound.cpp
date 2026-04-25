#include "Sound.h"
#include <iostream>

dae::Sound::Sound(const std::string& filepath, MIX_Mixer* mixer):
	m_mixer{mixer},
	m_filepath{filepath}
{
	
}

dae::Sound::~Sound()
{
	MIX_StopTrack(m_track, 0);
	MIX_DestroyTrack(m_track);
	MIX_DestroyAudio(m_sound);		
}

bool dae::Sound::IsLoaded() const
{
	return m_sound != nullptr;
}

void dae::Sound::Load()
{
	m_sound = MIX_LoadAudio(m_mixer, m_filepath.c_str(), false);
	if(not m_sound)
		std::cout << "LoadAudio error: " << SDL_GetError() << "\n";
	m_track = MIX_CreateTrack(m_mixer);
	if(not m_track)
		std::cout << "CreateTrack error: " << SDL_GetError() << "\n";
}

void dae::Sound::SetVolume(float volume)
{
	if (m_track)
		MIX_SetTrackGain(m_track, volume);
}

void dae::Sound::Play()
{
	MIX_SetTrackAudio(m_track, m_sound);
	MIX_PlayTrack(m_track, 0);
}
