#pragma once
#include "Component.h"
#include <memory>
#include "Subject.h"
#include "../Minigin/Observer.h"

namespace pacman
{
	class GhostComponent;
	class HealthComponent final : public dae::Component, public dae::Observer
	{
	public:
		HealthComponent(dae::GameObject* owner, int health = 4);
		~HealthComponent();
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent operator=(const HealthComponent& other) = delete;
		HealthComponent operator=(HealthComponent&& other) = delete;

		void TakeDamage(int amount);
		dae::Subject* GetTakeDamageEvent() { return m_takeDamageEvent.get(); }
		int GetHealth() const;
		virtual void OnCollision(dae::GameObject* other) override;
		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override;

		virtual void Update(float elapsedSec) override;
	private:
		int m_health;
		std::unique_ptr<dae::Subject> m_takeDamageEvent;
		const float m_maxInvincibleTime;
		float m_invincibleTime;
		bool m_isInvincible;
		bool m_canTakeDamage;

		void HandleDamage(pacman::GhostComponent* ghost);
	};
}
