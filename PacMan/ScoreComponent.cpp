#include "ScoreComponent.h"
#include "Events.h"
#include "Pellets.h"
#include "../Minigin/GameObject.h"
#include "FruitComponent.h"

int pacman::ScoreComponent::m_nrGhostsEaten{ 0 };

pacman::ScoreComponent::ScoreComponent(dae::GameObject* owner) :
	Component(owner)
{
	m_eventQueue.AddObserver(this);
}

pacman::ScoreComponent::~ScoreComponent()
{
	m_eventQueue.RemoveObserver(this);
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
	FruitComponent* fruit = other->GetComponent<FruitComponent>();
	if (fruit != nullptr)
	{
		m_score += fruit->GetValue();
		dae::Event event{ "FRUIT_PICKUP" };
		event.arg = std::make_unique<ScoreArg>(m_score);
		m_eventQueue.Invoke(std::move(event), GetGameObject());
	}
}

void pacman::ScoreComponent::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "GHOST_DIED")
	{
		const int baseValue{ 200 };
		++m_nrGhostsEaten;
		m_score += baseValue * m_nrGhostsEaten;
		dae::Event e{ "SCORE_CHANGED" };
		e.arg = std::make_unique<ScoreArg>(m_score);
		m_eventQueue.Invoke(std::move(e), GetGameObject());
	}
}
