#pragma once
#include "../Minigin/Component.h"
#include <vector>
#include <glm/glm.hpp>

namespace pacman
{
	enum class Direction
	{
		right,
		left,
		up,
		down
	};
	class TargetMoverComponent final : public dae::Component
	{
	public:
		TargetMoverComponent(dae::GameObject* owner, dae::GameObject* targetObj);
		void MoveToTarget(float elapsedSec);

	private:
		float m_moveSpeed{ 50.f };
		dae::GameObject* m_targetObj{};
		glm::vec2 m_nextDir{ 0,-1 };
		int m_gridIdx{};
		std::vector<int> m_neighbors;
		Direction m_dir{ Direction::up };

		void ChangeDirection();
	};
}