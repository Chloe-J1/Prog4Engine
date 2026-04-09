#include "HealthComponentUI.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "Event.h"

#include <iostream>
dae::HealthComponentUI::HealthComponentUI(GameObject* owner):
	Component(owner)
{
	m_spriteComp = GetGameObject()->GetComponent<SpriteComponent>();
	m_spriteComp->SetRow(3);
}

void dae::HealthComponentUI::Notify(GameObject*, const Event& event)
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
