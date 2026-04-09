#include "HealthComponentUI.h"
#include "GameObject.h"
#include "Event.h"

#include <iostream>
pacman::HealthComponentUI::HealthComponentUI(dae::GameObject* owner):
	Component(owner)
{
	m_spriteComp = GetGameObject()->GetComponent<dae::SpriteComponent>();
	m_spriteComp->SetRow(3);
}

void pacman::HealthComponentUI::Notify(dae::GameObject*, const Event& event)
{
	switch (event.id)
	{
	case EventId::PLAYER_TAKES_DAMAGE:
	{
		auto* healthArg = static_cast<UpdateHealthArg*>(event.arg.get());
		int health{ healthArg->health };
		m_spriteComp->SetRow(health - 1);
		break;
	}
	case EventId::PLAYER_DIED:
		GetGameObject()->SetIsAlive(false);
		// TODO: Remove observer from subject list
		break;
	default:
		break;
	}
}
