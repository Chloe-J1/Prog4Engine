#pragma once
#include "Component.h"
#include <memory>
#include "Subject.h"

namespace pacman
{
	class GhostComponent;
	class HealthComponent : public dae::Component
	{
	public:
		HealthComponent(dae::GameObject* owner, int health = 4);

		void TakeDamage(int amount);
		dae::Subject* GetTakeDamageEvent() { return m_takeDamageEvent.get(); }
		int GetHealth() const;
		virtual void OnCollision(dae::GameObject* other) override;

		virtual void Update(float elapsedSec);
	private:
		int m_health;
		std::unique_ptr<dae::Subject> m_takeDamageEvent;
		const float m_maxInvincibleTime;
		float m_invincibleTime;
		bool m_isInvincible;

		void HandleDamage(pacman::GhostComponent* ghost);
	};
}
