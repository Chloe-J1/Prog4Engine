#include "SoundManager.h"
#include "../Minigin/SoundSystem.h"
#include "../Minigin/ServiceLocator.h"

pacman::SoundManager::SoundManager()
{
	dae::EventQueue::GetInstance().AddObserver(this);

	dae::SoundSystem* ss = dae::ServiceLocator::GetSoundSystem();
	ss->RegisterSound("damage", "Data/Sound/death_1.wav");
	ss->RegisterSound("button", "Data/Sound/button.mp3");
	ss->RegisterSound("pickup_pellet", "Data/Sound/eat_dot.wav");
}

void pacman::SoundManager::Notify(dae::GameObject*, const dae::Event& event)
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
	}
	else if (event.id == "PELLET_PICKUP" || event.id == "POWER_PELLET_PICKUP")
	{
		ss->Play("pickup_pellet", volume);
	}
}
