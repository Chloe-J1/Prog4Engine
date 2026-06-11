#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/GameObject.h"

namespace pacman
{
	class TargetMoverComponent;
	class FruitComponent final : public dae::Component
	{
	public:
		explicit FruitComponent(dae::GameObject* owner);


		int GetValue() const;
	private:
		void Start();
		void OnCollision(dae::GameObject* other);
		void Update(float elapsecSec);

		const int m_windowWidth;
		const int m_windowHeight;
		static int m_nrFruit;
		const int m_value{ 300 };
		const float m_spriteWidth;
		TargetMoverComponent* m_moveComp{};
	};
}