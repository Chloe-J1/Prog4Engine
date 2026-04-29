#pragma once
#include <string>
#include <SDL3_mixer/SDL_mixer.h>
#include <memory>
namespace dae
{
	class Sound final
	{
	public:
		Sound(const std::string& filepath, MIX_Mixer* mixer);
		~Sound();

		bool IsLoaded() const;
		void Load();
		void SetVolume(float volume);
		void Play();
	private:
		class SoundImpl;
		std::unique_ptr<SoundImpl> m_impl;
	};
}