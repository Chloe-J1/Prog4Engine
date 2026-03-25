#pragma once
#include "Component.h"
#include "HealthComponent.h"
#include "Subject.h"
#include <memory>
#include "Event.h"
#include "Observer.h"
#include <iostream>
namespace dae
{
	class ScoreComponent : public Component, public Observer
	{
	public:
		ScoreComponent(GameObject* owner):
			Component(owner)
		{ 
			/*m_addScoreEvent = std::make_unique<Subject>();*/
		}

		/*Subject* GetAddScoreEvent() { return m_addScoreEvent.get(); }*/

		void AddScore(int amount)
		{
			m_score += amount;
			std::cout << "score added\n";
			

			//// Notify observers
			//m_addScoreEvent->NotifyObservers(GetGameObject(), Event{ EventId::ADD_SCORE });

			//if (m_score >= m_neededScore)
			//	m_addScoreEvent->NotifyObservers(GetGameObject(), Event{ EventId::GAME_WON });
		}
		int GetScore() const
		{
			return m_score;
		}

		virtual void Notify(GameObject*, Event event) override
		{
			if (event.id == EventId::PICKUP_PELLET)
			{
				PickupPelletEvent* pickupEvent = static_cast<PickupPelletEvent*>(event.args[0]);
				AddScore(pickupEvent->pellet->GetValue());
			}
		}

	private:
		int m_score{ 0 };
		/*std::unique_ptr<Subject> m_addScoreEvent;*/
		const int m_neededScore{ 500 };
	};
}
