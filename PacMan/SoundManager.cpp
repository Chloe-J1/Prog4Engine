#include "SoundManager.h"
#include "../Minigin/SoundSystem.h"
#include "../Minigin/ServiceLocator.h"

pacman::SoundManager::SoundManager()
{
	dae::EventQueue::GetInstance().AddEventHandler(this);

	dae::ISoundSystem* ss = dae::ServiceLocator::GetSoundSystem();
	ss->RegisterSound("damage", "Data/Sound/death_1.wav");
	ss->RegisterSound("button", "Data/Sound/button.mp3");
	ss->RegisterSound("pellet_pickup", "Data/Sound/eat_dot.wav");
	ss->RegisterSound("fruit_pickup", "Data/Sound/eat_fruit.wav");
	ss->RegisterSound("player_died", "Data/Sound/ms_death.wav");
	ss->RegisterSound("ghost_died", "Data/Sound/ms_eat_ghost.wav");
}

pacman::SoundManager::~SoundManager()
{
	dae::EventQueue::GetInstance().RemoveEventHandler(this);
}

void pacman::SoundManager::Notify(const dae::Event& event)
{
	const float volume{ 50 };
	dae::ISoundSystem* ss = dae::ServiceLocator::GetSoundSystem();
	if (event.id == "PLAYER_TAKES_DAMAGE")
	{
		ss->Play("damage", volume);
	}
	else if (event.id == "BUTTON_PRESSED")
	{
		ss->Play("button", volume);
	}
	else if (event.id == "PELLET_PICKUP" || event.id == "POWER_PELLET_PICKUP")
	{
		ss->Play("pellet_pickup", volume);
	}
	else if (event.id == "FRUIT_PICKUP")
	{
		ss->Play("fruit_pickup", volume);
	}
	else if (event.id == "PLAYER_DIED")
	{
		ss->Play("player_died", volume);
	}
	else if (event.id == "GHOST_DIED")
	{
		ss->Play("ghost_died", volume);
	}
}
