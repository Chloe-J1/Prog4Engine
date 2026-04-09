#include "HealthComponent.h"
#include "Subject.h"
#include "../PacMan/Ghost.h"
#include "Event.h"

dae::HealthComponent::HealthComponent(GameObject* owner, int health):
	Component(owner),
	m_health{health},
	m_takeDamageEvent{ std::make_unique<Subject>() },
	m_invincibleTime{0},
	m_maxInvincibleTime{0.7f},
	m_isInvincible{false}
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

void dae::HealthComponent::OnCollision(GameObject* other)
{
	pacman::GhostComponent* ghost = other->GetComponent<pacman::GhostComponent>();
	if (ghost != nullptr)
	{
		HandleDamage(ghost);
	}
}

void dae::HealthComponent::Update(float elapsedSec)
{
	if (m_isInvincible) // TODO: coroutine?
	{
		m_invincibleTime += elapsedSec;
		if (m_invincibleTime >= m_maxInvincibleTime)
		{
			m_isInvincible = false;
			m_invincibleTime = 0;
		}
	}
}

void dae::HealthComponent::HandleDamage(pacman::GhostComponent* ghost)
{
	if (not m_isInvincible)
	{
		m_health -= ghost->GetDamage();
		Event takeDamageEvent{ EventId::PLAYER_TAKES_DAMAGE };
		takeDamageEvent.arg = std::make_unique<UpdateHealthArg>(m_health);
		m_takeDamageEvent->NotifyObservers(GetGameObject(), std::move(takeDamageEvent));
		m_isInvincible = true;
		// Check death
		if (m_health <= 0)
		{
			Event deadEvent{ EventId::PLAYER_DIED };
			m_takeDamageEvent->NotifyObservers(GetGameObject(), std::move(deadEvent));
			GetGameObject()->SetIsAlive(false);
		}
	}
}

