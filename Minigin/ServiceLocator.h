#pragma once
#include <memory>
#include <SoundSystem.h>
namespace dae
{
	class ServiceLocator final
	{
		inline static std::unique_ptr<SoundSystem> m_soundSysInstance;
	public:
		static SoundSystem* GetSoundSystem();
		static void RegisterSoundsystem(std::unique_ptr<SoundSystem>&& soundSys);
	};
}