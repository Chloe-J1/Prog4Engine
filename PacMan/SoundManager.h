#pragma once
#include "../Minigin/EventQueue.h"
#include "../Minigin/Observer.h"
#include "../Minigin/SoundSystem.h"
#include "../Minigin/ServiceLocator.h"

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
			ss->RegisterSound("pickup_pellet", "Data/Sound/eat_dot.wav");
			
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
			const float volume{ 50 };
			dae::SoundSystem* ss = dae::ServiceLocator::GetSoundSystem();
			if (event.id == "PLAYER_TAKES_DAMAGE")
			{
				ss->Play("damage", volume);
				ss->Play("damage", volume);
			}
			else if (event.id == "BUTTON_PRESSED")
			{
				ss->Play("button", volume);
				SDL_Delay(100);
				ss->Play("button", volume);
			}
			else if (event.id == "PELLET_PICKUP")
			{
				ss->Play("pickup_pellet", volume);
			}
		}
	private:
	};
}