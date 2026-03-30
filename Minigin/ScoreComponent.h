#pragma once
#include "Component.h"
#include "Subject.h"
#include "Event.h"
#include "Pellets.h"

#include <iostream>
#include "Hitbox.h"
#include "CollisionManager.h"
namespace dae
{
	class ScoreComponent : public Component
	{
	public:
		ScoreComponent(GameObject* owner) :
			Component(owner),
			m_updateScoreEvent{ std::make_unique<Subject>() }
		{ 
		}

		Subject* GetSubject()
		{
			return m_updateScoreEvent.get();
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
				m_score += pellet->GetValue();
				Event updateScoreEvent{ EventId::UPDATE_SCORE };
				updateScoreEvent.arg = std::make_unique<UpdateScoreArg>( m_score );
				m_updateScoreEvent->NotifyObservers(GetGameObject(), std::move(updateScoreEvent));

				other->SetIsAlive(false);
			}
		}

	private:
		int m_score{ 0 };
		std::unique_ptr<Subject> m_updateScoreEvent;
	};
}
