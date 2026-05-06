#pragma once
#include "../Minigin/Component.h"
#include "GameObject.h"
#include "GhostState.h"
#include <memory>

namespace pacman
{
	class GhostComponent final : public dae::Component
	{
	public:
		GhostComponent(dae::GameObject* owner, std::unique_ptr<GhostState> state);

		int GetDamage() const;

		virtual void Update(float elapsedSec) override;

	private:
		int m_damage;
		std::unique_ptr<GhostState> m_ghostState{};
	};
}