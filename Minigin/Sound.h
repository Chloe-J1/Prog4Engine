#pragma once
#include <string>
#include <SDL3_mixer/SDL_mixer.h>
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
		MIX_Mixer* m_mixer;
		MIX_Track* m_track{};
		MIX_Audio* m_sound{};

		std::string m_filepath;
	};
}