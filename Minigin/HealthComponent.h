#pragma once
#include "Component.h"
#include <memory>
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
	private:
		int m_health;
		std::unique_ptr<Subject> m_takeDamageEvent;
	};
}
