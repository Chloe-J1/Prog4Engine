#pragma once
#include "../Minigin/EventQueue.h"
#include "../Minigin/Observer.h"


namespace pacman
{
	class SoundManager : public dae::Observer
	{
	public:
		SoundManager();
		~SoundManager()
		{
			dae::EventQueue::GetInstance().RemoveObserver(this);
		}
		SoundManager(const SoundManager& other) = delete;
		SoundManager(SoundManager&& other) = delete;
		SoundManager& operator=(const SoundManager& other) = delete;
		SoundManager& operator=(SoundManager&& other) = delete;

		virtual void Notify(dae::GameObject*, const dae::Event& event) override;
	};
}