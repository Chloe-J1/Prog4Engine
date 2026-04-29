//#include "Sound.h"
//#include <iostream>
//#include <SDL3_mixer/SDL_mixer.h>
//namespace dae
//{
//	class dae::Sound::SoundImpl final // Nested class
//	{
//	public:
//		SoundImpl(const std::string& filepath, MIX_Mixer* mixer):
//			m_mixer{ mixer },
//			m_filepath{ filepath }
//		{
//
//		}
//		~SoundImpl()
//		{
//			MIX_StopTrack(m_track, 0);
//			MIX_DestroyTrack(m_track);
//			MIX_DestroyAudio(m_sound);
//		}
//
//		bool IsLoaded() const
//		{
//			return m_sound != nullptr;
//		}
//		void Load()
//		{
//			m_sound = MIX_LoadAudio(m_mixer, m_filepath.c_str(), false);
//			if (not m_sound)
//				std::cout << "LoadAudio error: " << SDL_GetError() << "\n";
//			m_track = MIX_CreateTrack(m_mixer);
//			if (not m_track)
//				std::cout << "CreateTrack error: " << SDL_GetError() << "\n";
//		}
//		void SetVolume(float volume)
//		{
//			if (m_track)
//				MIX_SetTrackGain(m_track, volume);
//		}
//		void Play()
//		{
//			MIX_SetTrackAudio(m_track, m_sound);
//			MIX_PlayTrack(m_track, 0);
//		}
//	private:
//		MIX_Mixer* m_mixer;
//		MIX_Track* m_track{};
//		MIX_Audio* m_sound{};
//
//		std::string m_filepath;
//	};
//}
//dae::Sound::~Sound() = default;
//
//dae::Sound::Sound(const std::string& filepath, MIX_Mixer* mixer):
//	m_impl{std::make_unique<SoundImpl>(filepath, mixer)}
//{
//}
//
//
//bool dae::Sound::IsLoaded() const
//{
//	return m_impl->IsLoaded();
//}
//
//void dae::Sound::Load()
//{
//	m_impl->Load();
//}
//
//void dae::Sound::SetVolume(float volume)
//{
//	m_impl->SetVolume(volume);
//}
//
//void dae::Sound::Play()
//{
//	m_impl->Play();
//}
