#pragma once
#include "../Minigin/Component.h"
namespace pacman
{
	class AutoKill final : public dae::Component
	{
	public:
		explicit AutoKill(dae::GameObject* owner, float sec);
	private:
		void Update(float elaspedSec);

		float m_timer{};
		const float m_maxTime{};
	};
}