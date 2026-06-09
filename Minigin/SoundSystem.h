#pragma once
#include <memory>
#include <string>

namespace dae
{
	struct SoundMessage
	{
		std::string id;
		float volume;
	};

	// Interface used for sound service locator
	class ISoundSystem
	{
	public:
		virtual ~ISoundSystem() = default;
		virtual void Play(const std::string& soundId, const float volume) = 0;
		virtual void RegisterSound(const std::string& id, const std::string& path) = 0;
	};

	// Null sound system
	class NullSoundSystem final : public ISoundSystem
	{
	public:
		virtual void Play(const std::string&, const float) override {};
		virtual void RegisterSound(const std::string&, const std::string&) override {};
	};

	// SDL sound system
	class SDLSoundSystem final : public ISoundSystem
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
	class LoggingSoundSystem final : public ISoundSystem
	{
		std::unique_ptr<ISoundSystem> m_realSoundSys;
	public:
		LoggingSoundSystem(std::unique_ptr<ISoundSystem>&& soundSys);
		virtual ~LoggingSoundSystem() = default;
		LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem(LoggingSoundSystem&& other) = delete;
		LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem& operator=(LoggingSoundSystem&& other) = delete;

		virtual void Play(const std::string& soundId, const float volume) override;
		virtual void RegisterSound(const std::string& id, const std::string& path) override;
	};
}