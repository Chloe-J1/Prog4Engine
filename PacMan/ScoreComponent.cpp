#include "ScoreComponent.h"
#include "Events.h"
#include "Pellets.h"

pacman::ScoreComponent::ScoreComponent(dae::GameObject* owner) :
	Component(owner),
	m_updateScoreEvent{ std::make_unique<dae::Subject>() }
{
}

dae::Subject* pacman::ScoreComponent::GetSubject()
{
	return m_updateScoreEvent.get();
}

int pacman::ScoreComponent::GetScore() const
{
	return m_score;
}

void pacman::ScoreComponent::OnCollision(dae::GameObject* other)
{
	BasePellet* pellet = other->GetComponent<BasePellet>();
	if (pellet != nullptr)
	{
		m_score += pellet->GetValue();
		dae::Event updateScoreEvent{ "UPDATE_SCORE" }; // TODO: to specific name, make it general pickupEvent
		updateScoreEvent.arg = std::make_unique<UpdateScoreArg>(m_score);
		m_updateScoreEvent->NotifyObservers(GetGameObject(), std::move(updateScoreEvent));

		// TEMP
		if (dynamic_cast<PowerPellet*>(pellet) != nullptr)
		{
			dae::Event pickupEvent{ "POWER_PELLET_PICKUP" };
			dae::EventQueue().GetInstance().Invoke(std::move(pickupEvent), GetGameObject());
		}
		else
		{
			dae::Event pickupEvent{ "PELLET_PICKUP" };
			dae::EventQueue().GetInstance().Invoke(std::move(pickupEvent), GetGameObject());
			//
		}

		other->SetIsAlive(false);
	}
}
