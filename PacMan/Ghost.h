#pragma once
#include "../Minigin/Component.h"
#include "GameObject.h"
#include <vector>
#include <iostream>
#include "Graph.h"

#include <queue>
#include <unordered_map>
#include <algorithm>

namespace pacman
{
	enum class Direction
	{
		right,
		left,
		up,
		down
	};

	class GhostComponent final : public dae::Component
	{
	public:
		GhostComponent(dae::GameObject* owner) :
			Component(owner),
			m_damage{1},
			m_gridIdx{Graph::GetInstance().GetGridIdx(GetGameObject()->GetWorldPosition())}

		{
		}

		int GetDamage() const;

		virtual void Update(float elapsedSec) override;

		void SetTarget(dae::GameObject* targetObj);

	private:
		int m_damage;
		float m_moveSpeed{ 50.f };
		dae::GameObject* m_targetObj{};
		glm::vec2 m_nextDir{0,-1};
		int m_gridIdx{};
		std::vector<int> m_neighbors;
		Direction m_dir{ Direction::up };

		void ChangeDirection();
	};
}