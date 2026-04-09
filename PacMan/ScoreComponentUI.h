#pragma once
#include "Component.h"
#include "Observer.h"
#include "TextComponent.h"
#include <string>
#include "Event.h"

namespace dae
{
	class ScoreComponentUI : public Component, public Observer
	{
	public:
		ScoreComponentUI(GameObject* owner) :
			Component(owner)
		{
			m_textComponent = owner->GetComponent<TextComponent>();
		}

		virtual void Notify(GameObject*, const Event& event) override
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
		TextComponent* m_textComponent;
	};
}