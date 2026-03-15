#pragma once
#include "Component.h"
#include "HealthComponent.h"
#include "Subject.h"
#include <memory>
namespace dae
{
	class ScoreComponent : public Component
	{
	public:
		ScoreComponent(GameObject* owner):
			Component(owner)
		{ 
			m_addScoreEvent = std::make_unique<Subject>();
		}

		Subject* GetAddScoreEvent() { return m_addScoreEvent.get(); }

		void AddScore(int amount)
		{
			m_score += amount;
			

			// Notify observers
			m_addScoreEvent->NotifyObservers(GetGameObject(), Event::ADD_SCORE);

			if (m_score >= m_neededScore)
				m_addScoreEvent->NotifyObservers(GetGameObject(), Event::GAME_WON);
		}
		int GetScore() const
		{
			return m_score;
		}

	private:
		int m_score{ 0 };
		std::unique_ptr<Subject> m_addScoreEvent;
		const int m_neededScore{ 500 };
	};
}
