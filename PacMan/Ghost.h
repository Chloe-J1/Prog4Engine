#pragma once
#include "../Minigin/Component.h"
#include "GameObject.h"
namespace pacman
{
	class GhostComponent final : public dae::Component
	{
	public:
		GhostComponent(dae::GameObject* owner) :
			Component(owner),
			m_damage{1}
		{
		}

		int GetDamage() const
		{
			return m_damage;
		}

	private:
		int m_damage;
	};
}