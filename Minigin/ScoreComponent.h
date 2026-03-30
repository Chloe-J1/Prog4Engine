#pragma once
#include "Component.h"
#include "HealthComponent.h"
#include "Subject.h"
#include <memory>
#include "Event.h"
#include "EventQueue.h"
#include <iostream>
#include "Pellets.h"
namespace dae
{
	class ScoreComponent : public Component
	{
	public:
		ScoreComponent(GameObject* owner):
			Component(owner)
		{ 
		}


		int GetScore() const
		{
			return m_score;
		}

		
		virtual void OnCollision(GameObject* other) override
		{
			BasePellet* pellet = other->GetComponent<dae::SmallPellet>();
			if (pellet != nullptr)
			{
				/*Event scoreEvent{ EventId::PICKUP_PELLET };
				dae::EventQueue::GetInstance().Invoke(std::move(scoreEvent), GetGameObject());*/

				m_score += pellet->GetValue();
			}
		}

	private:
		int m_score{ 0 };
	};
}
