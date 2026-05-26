#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/GameObject.h"

namespace pacman
{
	class TargetMoverComponent;
	class FruitComponent final : public dae::Component
	{
	public:
		FruitComponent(dae::GameObject* owner);

		virtual void Start() override;

		int GetValue() const;
	private:
		virtual void OnCollision(dae::GameObject* other) override;
		virtual void Update(float elapsecSec) override;

		const int m_windowWidth;
		const int m_windowHeight;
		static int m_nrFruit;
		const int m_value{ 300 };
		const float m_spriteWidth;
		TargetMoverComponent* m_moveComp{};
	};
}