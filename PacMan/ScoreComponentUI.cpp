#include "ScoreComponentUI.h"
#include <string>
#include "Events.h"
#include "../Minigin/EventQueue.h"

pacman::ScoreComponentUI::ScoreComponentUI(dae::GameObject* owner, dae::GameObject* pacman) :
	Component(owner),
	m_pacman{pacman}
{
	m_textComponent = owner->GetComponent<dae::TextComponent>();
	dae::EventQueue::GetInstance().AddEventHandler(this);
}

pacman::ScoreComponentUI::~ScoreComponentUI()
{
	dae::EventQueue::GetInstance().RemoveEventHandler(this);
}

void pacman::ScoreComponentUI::Notify(const dae::Event& event)
{
	if (event.id == "GHOST_VALUE_CALCULATED" || event.id == "POWER_PELLET_PICKUP" || event.id == "PELLET_PICKUP" || event.id == "FRUIT_PICKUP")
	{
		auto* arg = static_cast<ScoreArg*>(event.arg.get());
		if (arg->sender == m_pacman)
		{
			int score{ arg->score };
			m_textComponent->SetText("Score: " + std::to_string(score));
		}
	}
}
