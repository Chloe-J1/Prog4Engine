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

		virtual void Play(const std::string& soundId, const float volume) override;
		virtual void RegisterSound(const std::string& id, const std::string& path) override;

		void ProcessRequests();
	private:
		std::unordered_map<std::string, std::unique_ptr<Sound>> m_soundMap;
		MIX_Mixer* m_mixer;

		std::queue<SoundMessage> m_pendingRequests;
		std::jthread m_thread;
		std::mutex m_mutex{};
		std::condition_variable m_conditionVar{};
		std::atomic<bool> m_isRunning{ true };
	};

	// Logging sound system
	class LoggingSoundSystem final : public SoundSystem
	{
		std::unique_ptr<SoundSystem> m_realSoundSys;
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSys);
		virtual ~LoggingSoundSystem() = default;

		virtual void Play(const std::string& soundId, const float volume) override;
		virtual void RegisterSound(const std::string& id, const std::string& path) override;
	};
}