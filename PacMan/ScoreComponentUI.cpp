#include "ScoreComponentUI.h"
#include <string>
#include "Events.h"
#include "../Minigin/EventQueue.h"

static int m_nrGhostsEaten{ 0 };

pacman::ScoreComponentUI::ScoreComponentUI(dae::GameObject* owner, dae::GameObject* pacman) :
	Component(owner),
	m_pacman{pacman}
{
	m_textComponent = owner->GetComponent<dae::TextComponent>();
	dae::EventQueue::GetInstance().AddObserver(this);
}

pacman::ScoreComponentUI::~ScoreComponentUI()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::ScoreComponentUI::Notify(dae::GameObject* sender, const dae::Event& event)
{
	if (m_pacman != sender) return;
	if (event.id == "SCORE_CHANGED" || event.id == "POWER_PELLET_PICKUP" || event.id == "PELLET_PICKUP")
	{
		auto* arg = static_cast<ScoreArg*>(event.arg.get());
		int score{ arg->score };
		m_textComponent->SetText("Score: " + std::to_string(score));
	}
}
