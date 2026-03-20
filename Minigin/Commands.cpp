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
	go->GetComponent<dae::HealthComponent>()->TakeDamage(amount);
	go->GetComponent <dae::HealthComponent>()->GetTakeDamageEvent()->NotifyObservers(go, Event::PLAYER_TAKES_DAMAGE);
}

// SCORE
//********
void dae::Score::Execute(float)
{
	const int amount{ 100 };
	GetGameObject()->GetComponent<dae::ScoreComponent>()->AddScore(amount);
	
}
