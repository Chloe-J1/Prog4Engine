#pragma once
#include <memory>
#include "SoundSystem.h"
namespace dae
{
	class ServiceLocator final
	{
		inline static std::unique_ptr<ISoundSystem> m_soundSysInstance;
	public:
		static ISoundSystem* GetSoundSystem();
		static void RegisterSoundsystem(std::unique_ptr<ISoundSystem>&& soundSys);
	};
}