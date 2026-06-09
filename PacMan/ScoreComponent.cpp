#include "ScoreComponent.h"
#include "Events.h"
#include "Pellets.h"
#include "../Minigin/GameObject.h"
#include "FruitComponent.h"
#include <nlohmann/json.hpp>
#include <fstream>

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

	// New highscore?
	CheckForHighscore();
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
		m_eventQueue.Invoke(std::move(pickupEvent));

		other->SetIsAlive(false);
	}
	FruitComponent* fruit = other->GetComponent<FruitComponent>();
	if (fruit != nullptr)
	{
		m_score += fruit->GetValue();
		dae::Event event{ "FRUIT_PICKUP" };
		event.arg = std::make_unique<ScoreArg>(m_score);
		m_eventQueue.Invoke(std::move(event));
	}
}

void pacman::ScoreComponent::Notify(const dae::Event& event)
{
	if (event.id == "GHOST_DIED")
	{
		const int baseValue{ 200 };
		++m_nrGhostsEaten;
		m_score += baseValue * m_nrGhostsEaten;
		dae::Event e{ "SCORE_CHANGED" };
		e.arg = std::make_unique<ScoreArg>(m_score);
		m_eventQueue.Invoke(std::move(e));
	}
}

void pacman::ScoreComponent::CheckForHighscore()
{
	const int m_maxNrHighscores{ 3 };
	std::filesystem::path filepath = std::filesystem::path(DATA_PATH) / "Scores.json";
	std::ifstream iFile(filepath);

	nlohmann::json data = nlohmann::json::parse(iFile);
	auto& highscores = data["Highscores"];
	if (highscores.size() < m_maxNrHighscores || m_score > highscores.back()["score"])
	{
		if(highscores.size() >= m_maxNrHighscores)
			highscores.erase(m_maxNrHighscores - 1); // remove lowest value
		std::string playerName = data["CurrentPlayers"][m_controllerIdx]["name"];
		highscores.push_back({
			{"name", playerName},
			{"score", m_score}
		});
		std::sort(highscores.begin(), highscores.end(), [](auto val1, auto val2) {
				return val1["score"] > val2["score"];
			});

		std::ofstream oFile(filepath);
		oFile << data.dump(4);
		oFile.close();
	}
}
