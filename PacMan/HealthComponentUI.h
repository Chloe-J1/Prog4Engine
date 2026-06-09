#pragma once
#include "Component.h"
#include "IObserver.h"
#include "SpriteComponent.h"
namespace pacman
{
	class HealthComponentUI final : public dae::Component, public dae::IObserver
	{
	public:
		HealthComponentUI(dae::GameObject* owner, dae::GameObject* pacman);
		~HealthComponentUI();
		HealthComponentUI(const HealthComponentUI& other) = delete;
		HealthComponentUI(HealthComponentUI&& other) = delete;
		HealthComponentUI& operator=(const HealthComponentUI& other) = delete;
		HealthComponentUI& operator=(HealthComponentUI&& other) = delete;

		virtual void Notify(dae::GameObject* gameObject, const dae::Event& event) override;
	private:
		dae::SpriteComponent* m_spriteComp;
		dae::GameObject* m_pacman;
	};
}
