#include "ServiceLocator.h"

dae::ISoundSystem* dae::ServiceLocator::GetSoundSystem()
{
	return m_soundSysInstance.get();
}

void dae::ServiceLocator::RegisterSoundsystem(std::unique_ptr<ISoundSystem>&& soundSys)
{
	if (soundSys == nullptr)
	{
		m_soundSysInstance = std::make_unique<dae::NullSoundSystem>();
	}
	else
	{
		m_soundSysInstance = std::move(soundSys);
	}
}
