#pragma once
#include "Component.h"
#include "Observer.h"
#include "TextComponent.h"
#include <string>
#include "Events.h"

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

		virtual void Notify(dae::GameObject*, const dae::Event& event) override
		{
			if(event.id == "UPDATE_SCORE")
			{
				auto* updateArg = static_cast<UpdateScoreArg*>(event.arg.get());
				int score{ updateArg->score };
				m_textComponent->SetText("Score: " + std::to_string(score));
			}
		}
		

	private:
		dae::TextComponent* m_textComponent;
	};
}