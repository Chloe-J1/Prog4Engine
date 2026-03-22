#include "HealthComponentUI.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"

#include <iostream>
dae::HealthComponentUI::HealthComponentUI(GameObject* owner):
	Component(owner)
{
	m_spriteComp = GetGameObject()->GetComponent<SpriteComponent>();
	m_spriteComp->SetRow(3);
}

void dae::HealthComponentUI::Notify(GameObject* gameObject, Event event)
{
	switch (event)
	{
	case dae::Event::PLAYER_TAKES_DAMAGE:
	{
		int health{ gameObject->GetComponent<HealthComponent>()->GetHealth()  };
		m_spriteComp->SetRow(health - 1);
		break;
	}
	case dae::Event::PLAYER_DIED:
		std::cout << "dead\n";
		GetGameObject()->SetIsAlive(false);
		// TODO: Remove observer from subject list
		break;
	default:
		break;
	}
}
