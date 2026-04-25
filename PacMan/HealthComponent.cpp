#include "HealthComponent.h"
#include "../PacMan/Ghost.h"
#include "Events.h"

#include "../Minigin/ServiceLocator.h"

pacman::HealthComponent::HealthComponent(dae::GameObject* owner, int health):
	Component(owner),
	m_health{health},
	m_takeDamageEvent{ std::make_unique<dae::Subject>() },
	m_maxInvincibleTime{0.7f},
	m_invincibleTime{0},
	m_isInvincible{false}
{
	dae::SoundSystem* ss = dae::ServiceLocator::GetSoundSystem();
	ss->RegisterSound(0, "Data/Sound/death_1.wav");
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
		dae::SoundSystem* ss = dae::ServiceLocator::GetSoundSystem();
		ss->Play(0, 50);
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
	if (not m_isInvincible)
	{
		m_health -= ghost->GetDamage();

		dae::Event takeDamageEvent{ "PLAYER_TAKES_DAMAGE" };
		takeDamageEvent.arg = std::make_unique<UpdateHealthArg>(m_health);
		m_takeDamageEvent->NotifyObservers(GetGameObject(), std::move(takeDamageEvent));
		m_isInvincible = true;
		// Check death
		if (m_health <= 0)
		{
			dae::Event deadEvent{"PLAYER_DIED"};
			m_takeDamageEvent->NotifyObservers(GetGameObject(), std::move(deadEvent));
			GetGameObject()->SetIsAlive(false);
		}
	}
}

