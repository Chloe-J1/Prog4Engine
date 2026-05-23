#include "HealthComponentUI.h"
#include "GameObject.h"
#include "Events.h"
#include "../Minigin/EventQueue.h"

pacman::HealthComponentUI::HealthComponentUI(dae::GameObject* owner, dae::GameObject* pacman):
	Component(owner),
	m_pacman{pacman}
{
	m_spriteComp = GetGameObject()->GetComponent<dae::SpriteComponent>();
	m_spriteComp->SetRow(3);
	dae::EventQueue::GetInstance().AddObserver(this);
}

pacman::HealthComponentUI::~HealthComponentUI()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::HealthComponentUI::Notify(dae::GameObject* sender, const dae::Event& event)
{
	if (sender != m_pacman) return;
	if (event.id == "PLAYER_TAKES_DAMAGE")
	{
		auto* healthArg = static_cast<UpdateHealthArg*>(event.arg.get());
		int health{ healthArg->health };
		m_spriteComp->SetRow(health - 1);
	}
	else if (event.id == "PLAYER_DIED")
	{
		GetGameObject()->SetIsAlive(false);
	}
}
