#pragma once
#include "Component.h"
#include <memory>
namespace pacman
{
	class GhostComponent;
}
namespace dae
{
	
	class Subject;
	class HealthComponent : public Component
	{
	public:
		HealthComponent(GameObject* owner, int health = 4);

		void TakeDamage(int amount);
		Subject* GetTakeDamageEvent() { return m_takeDamageEvent.get(); }
		int GetHealth() const;
		virtual void OnCollision(GameObject* other) override;

		virtual void Update(float elapsedSec);
	private:
		int m_health;
		std::unique_ptr<Subject> m_takeDamageEvent;
		const float m_maxInvincibleTime;
		float m_invincibleTime;
		bool m_isInvincible;

		void HandleDamage(pacman::GhostComponent* ghost);
	};
}
