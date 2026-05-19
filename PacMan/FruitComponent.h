#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/GameObject.h"

namespace pacman
{
	class FruitComponent final : public dae::Component
	{
	public:
		FruitComponent(dae::GameObject* owner);

	private:
		virtual void OnCollision(dae::GameObject* other) override;

		const int m_windowWidth;
		const int m_windowHeight;
		static int m_nrFruit;
	};
}