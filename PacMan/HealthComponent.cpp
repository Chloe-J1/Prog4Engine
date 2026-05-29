#include "HealthComponent.h"
#include "../PacMan/GhostComponent.h"
#include "Events.h"

pacman::HealthComponent::HealthComponent(dae::GameObject* owner, int health):
	Component(owner),
	m_initHealth{health},
	m_health{health},
	m_maxInvincibleTime{0.7f},
	m_invincibleTime{0},
	m_isInvincible{false},
	m_canTakeDamage{true}
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

pacman::HealthComponent::~HealthComponent()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::HealthComponent::TakeDamage(int amount)
{
	m_health -= amount;
}

int pacman::HealthComponent::GetHealth() const
{
	return m_health;
}

void pacman::HealthComponent::OnCollision(dae::GameObject* other)
{
	pacman::GhostComponent* ghost = other->GetComponent<pacman::GhostComponent>();
	if (ghost != nullptr)
	{
		HandleDamage(ghost);
	}
}

void pacman::HealthComponent::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "POWER_PELLET_PICKUP")
	{
		m_canTakeDamage = false;
	}
	else if (event.id == "NOT_DIZZIED")
	{
		m_canTakeDamage = true;
	}
}

void pacman::HealthComponent::Update(float elapsedSec)
{
	if (m_isInvincible)
	{
		m_invincibleTime += elapsedSec;
		if (m_invincibleTime >= m_maxInvincibleTime)
		{
			m_isInvincible = false;
			m_invincibleTime = 0;
		}
	}
}



void pacman::HealthComponent::HandleDamage(pacman::GhostComponent* ghost)
{
	if (not m_isInvincible && m_canTakeDamage)
	{
		m_health -= ghost->GetDamage();

		dae::Event takeDamageEvent{ "PLAYER_TAKES_DAMAGE" };

		// Check death
		if (m_health <= 0)
		{
			if (m_nrExtraLives <= 0)
			{
				dae::Event event{ "PLAYER_DIED" };
				m_eventQueue.Invoke(std::move(event), GetGameObject());
				GetGameObject()->SetIsAlive(false);
			}
			--m_nrExtraLives;
			m_health = m_initHealth;
		}

		takeDamageEvent.arg = std::make_unique<UpdateHealthArg>(m_health);
		dae::EventQueue::GetInstance().Invoke(std::move(takeDamageEvent), GetGameObject());

		m_isInvincible = true;
		
	}
}

