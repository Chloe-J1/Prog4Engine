#pragma once
#include <unordered_map>
#include <memory>
#include "Sound.h"
#include <SDL3_mixer/SDL_mixer.h>

namespace dae
{
	// Interface used for sound service locator
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(int soundId, const float volume) = 0;
		virtual void RegisterSound(int id, const std::string& path) = 0;
	};

	// SDL sound system
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();

		virtual void Play(int soundId, const float volume) override;
		void RegisterSound(int id, const std::string& path);
	private:
		std::unordered_map<int, std::unique_ptr<Sound>> m_soundMap;
		MIX_Mixer* m_mixer;
	};

}