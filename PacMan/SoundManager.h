#pragma once
#include "../Minigin/EventQueue.h"
#include "../Minigin/Observer.h"
#include "../Minigin/SoundSystem.h"
#include "../Minigin/ServiceLocator.h"
#include <iostream>
namespace pacman
{
	class SoundManager : public dae::Observer
	{
	public:
		SoundManager()
		{
			dae::EventQueue::GetInstance().AddObserver(this);

			dae::SoundSystem* ss = dae::ServiceLocator::GetSoundSystem();
			ss->RegisterSound("damage", "Data/Sound/death_1.wav");
			ss->RegisterSound("button", "Data/Sound/button.mp3");
		}
		~SoundManager()
		{
			dae::EventQueue::GetInstance().RemoveObserver(this);
		}
		SoundManager(const SoundManager& other) = delete;
		SoundManager(SoundManager&& other) = delete;
		SoundManager& operator=(const SoundManager& other) = delete;
		SoundManager& operator=(SoundManager&& other) = delete;

		virtual void Notify(dae::GameObject*, const dae::Event& event) override
		{
			dae::SoundSystem* ss = dae::ServiceLocator::GetSoundSystem();
			if (event.id == "PLAYER_TAKES_DAMAGE")
			{
				ss->Play("damage", 50);
			}
			else if (event.id == "BUTTON_PRESSED")
			{
				ss->Play("button", 50);
			}
		}
	private:
	};
}