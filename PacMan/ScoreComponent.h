#pragma once
#include "Component.h"
#include "../Minigin/EventQueue.h"

namespace dae
{
	class EventQueue;
}

namespace pacman
{
	class ScoreComponent : public dae::Component
	{
	public:
		ScoreComponent(dae::GameObject* owner);

		int GetScore() const;

		
		virtual void OnCollision(dae::GameObject* other) override;

	private:
		int m_score{ 0 };
		dae::EventQueue& m_eventQueue{ dae::EventQueue::GetInstance() };
	};
}
