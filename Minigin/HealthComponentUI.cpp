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

void dae::HealthComponentUI::Notify(GameObject* gameObject, Event event)
{
	switch (event.id)
	{
	case EventId::PLAYER_TAKES_DAMAGE:
	{
		int health{ gameObject->GetComponent<HealthComponent>()->GetHealth()  };
		m_spriteComp->SetRow(health - 1);
		break;
	}
	case EventId::PLAYER_DIED:
		std::cout << "dead\n";
		GetGameObject()->SetIsAlive(false);
		// TODO: Remove observer from subject list
		break;
	default:
		break;
	}
}
