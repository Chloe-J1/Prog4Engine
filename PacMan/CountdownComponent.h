#pragma once
#include "../Minigin/Component.h"
namespace pacman
{
	class CountdownComponent final : public dae::Component
	{
	public:
		explicit CountdownComponent(dae::GameObject* owner);
	private:
		float m_timer{};
		const float m_maxTime{ 3.f };

		void Update(float elapsedSec);
	};
}
