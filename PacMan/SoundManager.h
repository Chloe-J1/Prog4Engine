#pragma once
#include "../Minigin/EventQueue.h"
#include "../Minigin/IEventHandler.h"
#include "../Minigin/Singleton.h"

namespace pacman
{
	class SoundManager final : public dae::IEventHandler, public dae::Singleton<SoundManager>
	{
	public:
		SoundManager();
		~SoundManager();
		SoundManager(const SoundManager& other) = delete;
		SoundManager(SoundManager&& other) = delete;
		SoundManager& operator=(const SoundManager& other) = delete;
		SoundManager& operator=(SoundManager&& other) = delete;

		void Notify(const dae::Event& event);
		void RegisterSound();
	};
}