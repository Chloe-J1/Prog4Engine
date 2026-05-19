#include "ScoreComponentUI.h"
#include <string>
#include "Events.h"

pacman::ScoreComponentUI::ScoreComponentUI(dae::GameObject* owner) :
	Component(owner)
{
	m_textComponent = owner->GetComponent<dae::TextComponent>();
}

void pacman::ScoreComponentUI::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "UPDATE_SCORE")
	{
		auto* updateArg = static_cast<UpdateScoreArg*>(event.arg.get());
		int score{ updateArg->score };
		m_textComponent->SetText("Score: " + std::to_string(score));
	}
}
