#pragma once
#include "Component.h"
#include "../Minigin/Observer.h"
#include "../Minigin/EventQueue.h"

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
		int GetHealth() const;
		virtual void OnCollision(dae::GameObject* other) override;
		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override;

		virtual void Update(float elapsedSec) override;
	private:
		const int m_initHealth;
		int m_health;
		int m_nrExtraLives{ 3 };
		const float m_maxInvincibleTime;
		float m_invincibleTime;
		bool m_isInvincible;
		bool m_canTakeDamage;
		dae::EventQueue& m_eventQueue{dae::EventQueue::GetInstance()};

		void HandleDamage(pacman::GhostComponent* ghost);
	};
}
