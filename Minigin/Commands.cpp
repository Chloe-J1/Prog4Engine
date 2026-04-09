#include "Commands.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

#include <iostream>

// MOVE
//********
void dae::Move::Execute(float elapsedSec)
{
	m_moveComp->Move(m_speed, m_direction, elapsedSec);
}

// DAMAGE
//********
void dae::Damage::Execute(float)
{
	const int amount{ 1 };
	GameObject* go{ GetGameObject() };
	HealthComponent* healthComp{ go->GetComponent<HealthComponent>() };
	Subject* subject{ healthComp->GetTakeDamageEvent() };

	healthComp->TakeDamage(amount);

	// Notify observers
	subject->NotifyObservers(go, Event{ EventId::PLAYER_TAKES_DAMAGE });

	if (healthComp->GetHealth() <= 0)
	{
		subject->NotifyObservers(go, Event{ EventId::PLAYER_DIED });
	}
}
