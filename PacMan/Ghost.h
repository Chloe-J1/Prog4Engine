#pragma once
#include "../Minigin/Component.h"
#include "GameObject.h"
#include "GhostState.h"


namespace pacman
{
	class GhostComponent final : public dae::Component
	{
	public:
		GhostComponent(dae::GameObject* owner, dae::GameObject* targetObj);

		int GetDamage() const;

		virtual void Update(float elapsedSec) override;

	private:
		int m_damage;
		GhostState* m_ghostState{};
	};
}