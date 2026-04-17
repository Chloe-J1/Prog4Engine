#pragma once
#include "Component.h"
#include "Subject.h"
#include "Events.h"
#include "Pellets.h"

namespace pacman
{
	class ScoreComponent : public dae::Component
	{
	public:
		ScoreComponent(dae::GameObject* owner) :
			Component(owner),
			m_updateScoreEvent{ std::make_unique<dae::Subject>() }
		{ 
		}

		dae::Subject* GetSubject()
		{
			return m_updateScoreEvent.get();
		}

		int GetScore() const
		{
			return m_score;
		}

		
		virtual void OnCollision(dae::GameObject* other) override
		{
			BasePellet* pellet = other->GetComponent<BasePellet>();
			if (pellet != nullptr)
			{
				m_score += pellet->GetValue();
				dae::Event updateScoreEvent{ dae::EventId::UPDATE_SCORE };
				updateScoreEvent.arg = std::make_unique<UpdateScoreArg>( m_score );
				m_updateScoreEvent->NotifyObservers(GetGameObject(), std::move(updateScoreEvent));

				other->SetIsAlive(false);
			}
		}

	private:
		int m_score{ 0 };
		std::unique_ptr<dae::Subject> m_updateScoreEvent;
	};
}
