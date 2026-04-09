#pragma once
#include "Component.h"
#include "Observer.h"
#include "SpriteComponent.h"
namespace pacman
{
	class HealthComponentUI : public dae::Component, public dae::Observer
	{
	public:
		HealthComponentUI(dae::GameObject* owner);

		virtual void Notify(dae::GameObject* gameObject, const Event& event) override;
	private:
		dae::SpriteComponent* m_spriteComp;
	};
}
