#include "ScoreComponent.h"
#include "Events.h"
#include "Pellets.h"
#include "../Minigin/GameObject.h"
#include "FruitComponent.h"
#include "HighscoreParser.h"

int pacman::ScoreComponent::m_nrGhostsEaten{ 0 };

pacman::ScoreComponent::ScoreComponent(dae::GameObject* owner, int controllerIdx) :
	Component(owner),
	m_controllerIdx{ controllerIdx }
{
	m_eventQueue.AddEventHandler(this);
}

pacman::ScoreComponent::~ScoreComponent()
{
	m_eventQueue.RemoveEventHandler(this);
	HighscoreParser::GetInstance().UpdateScore(m_score, m_controllerIdx);
	HighscoreParser::GetInstance().UpdateHighscores();
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
		pickupEvent.arg = std::make_unique<ScoreArg>(m_score, pellet->GetValue(), GetGameObject());
		m_eventQueue.Invoke(std::move(pickupEvent));

		other->SetIsAlive(false);
	}
	FruitComponent* fruit = other->GetComponent<FruitComponent>();
	if (fruit != nullptr)
	{
		m_score += fruit->GetValue();
		dae::Event event{ "FRUIT_PICKUP" };
		event.arg = std::make_unique<ScoreArg>(m_score, fruit->GetValue(), GetGameObject());
		m_eventQueue.Invoke(std::move(event));
	}
}

void pacman::ScoreComponent::Notify(const dae::Event& event)
{
	if (event.id == "GHOST_DIED")
	{
		const int baseValue{ 200 };
		auto* arg = static_cast<GhostDiedArg*>(event.arg.get());
		if (arg->killer == GetGameObject())
		{
			++m_nrGhostsEaten;
			int addedValue{ baseValue * m_nrGhostsEaten };
			m_score += addedValue;
			dae::Event e{ "GHOST_VALUE_CALCULATED" };
			e.arg = std::make_unique<ScoreArg>(m_score, addedValue, GetGameObject());
			m_eventQueue.Invoke(std::move(e));
		}
	}
}
