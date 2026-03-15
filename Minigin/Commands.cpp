#include "Commands.h"
#include "GameObject.h"
#include "HealthComponent.h"


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
	GetGameObject()->GetComponent<dae::HealthComponent>()->TakeDamage(1);
}
