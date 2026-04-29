#pragma once
#include <unordered_map>
#include <memory>
#include "Sound.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <string>

namespace dae
{
	struct SoundMessage
	{
		std::string id;
		float volume;
	};

	// Interface used for sound service locator
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const std::string& soundId, const float volume) = 0;
		virtual void RegisterSound(const std::string& id, const std::string& path) = 0;
	};

	// SDL sound system
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		virtual void Play(const std::string& soundId, const float volume) override;
		virtual void RegisterSound(const std::string& id, const std::string& path) override;
	private:
		class SoundSystemImpl;
		std::unique_ptr<SoundSystemImpl> m_impl;
	};

	// Logging sound system
	class LoggingSoundSystem final : public SoundSystem
	{
		std::unique_ptr<SoundSystem> m_realSoundSys;
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSys);
		virtual ~LoggingSoundSystem() = default;
		LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem(LoggingSoundSystem&& other) = delete;
		LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem& operator=(LoggingSoundSystem&& other) = delete;

		virtual void Play(const std::string& soundId, const float volume) override;
		virtual void RegisterSound(const std::string& id, const std::string& path) override;
	};
}