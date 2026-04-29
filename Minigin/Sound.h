//#pragma once
//#include <string>
//#include <memory>
//#include <SDL3_mixer/SDL_mixer.h>
//namespace dae
//{
//	class Sound final
//	{
//	public:
//		Sound(const std::string& filepath, MIX_Mixer* mixer);
//		~Sound();
//		Sound(const Sound& other) = delete;
//		Sound(Sound&& other) = delete;
//		Sound operator=(const Sound& other) = delete;
//		Sound operator=(Sound&& other) = delete;
//
//		bool IsLoaded() const;
//		void Load();
//		void SetVolume(float volume);
//		void Play();
//	private:
//		class SoundImpl;
//		std::unique_ptr<SoundImpl> m_impl;
//	};
//}