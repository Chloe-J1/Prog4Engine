#include "Commands.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

#include <iostream>

// MOVE
//********
void dae::Move::Execute(float elapsedSec)
{
	GetGameObject()->AddLocalPosition(m_direction * m_speed * elapsedSec);
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
