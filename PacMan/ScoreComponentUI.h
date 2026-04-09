#pragma once
#include "Component.h"
#include "Observer.h"
#include "TextComponent.h"
#include <string>
#include "Event.h"

namespace pacman
{
	class ScoreComponentUI : public dae::Component, public dae::Observer
	{
	public:
		ScoreComponentUI(dae::GameObject* owner) :
			Component(owner)
		{
			m_textComponent = owner->GetComponent<dae::TextComponent>();
		}

		virtual void Notify(dae::GameObject*, const Event& event) override
		{
			switch (event.id)
			{
			case EventId::UPDATE_SCORE:
			{
				auto* updateArg = static_cast<UpdateScoreArg*>(event.arg.get());
				int score{ updateArg->score };
				m_textComponent->SetText("Score: " + std::to_string(score));
				break;
			}
			case EventId::GAME_WON:

				break;
			default:
				break;
			}
		}
		

	private:
		dae::TextComponent* m_textComponent;
	};
}