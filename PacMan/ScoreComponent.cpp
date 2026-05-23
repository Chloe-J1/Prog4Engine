#include "ScoreComponent.h"
#include "Events.h"
#include "Pellets.h"
#include "../Minigin/GameObject.h"

pacman::ScoreComponent::ScoreComponent(dae::GameObject* owner) :
	Component(owner)
{
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

		std::string eventID{};
		if (dynamic_cast<PowerPellet*>(pellet) != nullptr)
		{
			eventID = "POWER_PELLET_PICKUP";
		}
		else
		{
			eventID = "PELLET_PICKUP";
		}

		dae::Event pickupEvent{ eventID };
		pickupEvent.arg = std::make_unique<ScoreArg>(m_score);
		m_eventQueue.Invoke(std::move(pickupEvent), GetGameObject());

		other->SetIsAlive(false);
	}
}
