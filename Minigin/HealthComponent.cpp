#include "HealthComponent.h"
#include "Subject.h"

#include <iostream>

dae::HealthComponent::HealthComponent(GameObject* owner, int health):
	Component(owner),
	m_health{health},
	m_takeDamageEvent{ std::make_unique<Subject>() }
{
}

void dae::HealthComponent::TakeDamage(int amount)
{
	m_health -= amount;
}

int dae::HealthComponent::GetHealth() const
{
	return m_health;
}
