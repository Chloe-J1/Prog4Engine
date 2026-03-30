#pragma once
#include "Component.h"
#include "Observer.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
#include <string>
#include "EventQueue.h"

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

		virtual void Notify(GameObject* gameObject, const Event& event) override
		{
			switch (event.id)
			{
			case EventId::PICKUP_PELLET:
			{
				int score{ gameObject->GetComponent<ScoreComponent>()->GetScore() };
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