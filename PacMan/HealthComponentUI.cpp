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
	dae::EventQueue::GetInstance().AddEventHandler(this);
}

pacman::HealthComponentUI::~HealthComponentUI()
{
	dae::EventQueue::GetInstance().RemoveEventHandler(this);
}

void pacman::HealthComponentUI::Notify(const dae::Event& event)
{
	if (event.id == "PLAYER_TAKES_DAMAGE")
	{
		auto* healthArg = static_cast<UpdateHealthArg*>(event.arg.get());
		int health{ healthArg->health };
		if(healthArg->sender == m_pacman)
			m_spriteComp->SetRow(health - 1);
	}
	else if (event.id == "PLAYER_DIED")
	{
		auto* arg = static_cast<SenderArg*>(event.arg.get());
		if (arg->sender == m_pacman)
			GetGameObject()->SetIsAlive(false);
	}
}
