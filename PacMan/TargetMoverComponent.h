#pragma once
#include "../Minigin/Component.h"
#include <vector>
#include <glm/glm.hpp>
#include "Graph.h"
#include <unordered_map>

namespace pacman
{
	class TargetMoverComponent final : public dae::Component
	{
	public:
		TargetMoverComponent(dae::GameObject* owner);
		void MoveToTarget(float elapsedSec);
		void MoveAwayTarget(float elapsedSec);
		void MoveFrontTarget(float elapsedSec);
		bool MoveToCell(int gridIdx, float elapsedSec);
		
		void SetTargetObj(dae::GameObject* newTarget);
	private:
		float m_moveSpeed{ 50.f };
		dae::GameObject* m_targetObj{};
		glm::vec2 m_targetPos{};
		glm::vec2 m_nextDir{ 0,-1 };
		int m_gridIdx{};
		int m_targetGridIdx{ -1 };
		std::vector<int> m_neighbors;
		const float m_spriteWidth;
		const float m_spriteHeight;
		Graph& m_graph;

		void ChangeDirection(bool isMovingAway);
		bool IsInNewCell();
		void Move(float elapsedSec);
	};
}