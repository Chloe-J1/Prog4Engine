#pragma once
#include "Component.h"
#include "Observer.h"
namespace dae
{
	class SpriteComponent;
	class HealthComponentUI : public Component, public Observer
	{
	public:
		HealthComponentUI(GameObject* owner);

		virtual void Notify(GameObject* gameObject, const Event& event) override;
	private:
		SpriteComponent* m_spriteComp;
	};
}
