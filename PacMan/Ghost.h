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

		int GetDamage() const
		{
			return m_damage;
		}

		virtual void Update(float elapsedSec) override
		{
			const float spriteSize{ 24 };
			const float halfSpriteSize{ spriteSize / 2.f };
			glm::vec2 centerPos{ GetGameObject()->GetWorldPosition() };
			centerPos.x += halfSpriteSize;
			centerPos.y += halfSpriteSize;
			glm::vec2 furthestPos{centerPos};
			switch (m_dir)
			{
			case pacman::Direction::right:
				furthestPos.x -= halfSpriteSize;
				break;
			case pacman::Direction::left:
				furthestPos.x += halfSpriteSize;
				break;
			case pacman::Direction::up:
				furthestPos.y += halfSpriteSize;
				break;
			case pacman::Direction::down:
				furthestPos.y -= halfSpriteSize;
				break;
			}

			int newGridIdx{ Graph::GetInstance().GetGridIdx(furthestPos) };
			if (newGridIdx != m_gridIdx)
			{
				m_gridIdx = newGridIdx;
				ChangeDirection();
			}

			GetGameObject()->AddLocalPosition(m_nextDir * m_moveSpeed * elapsedSec);
		}

		void SetTarget(dae::GameObject* targetObj)
		{
			m_targetObj = targetObj;
		}

	private:
		int m_damage;
		float m_moveSpeed{ 50.f };
		dae::GameObject* m_targetObj{};
		glm::vec2 m_nextDir{0,-1};
		int m_gridIdx{};
		std::vector<int> m_neighbors;
		Direction m_dir{ Direction::up };

		void ChangeDirection()
		{
			std::cout << "gridIdx: " << m_gridIdx << " exists: " << Graph::GetInstance().HasIndex(m_gridIdx) << "\n";
			m_neighbors = Graph::GetInstance().GetNeighbors(m_gridIdx);
			if (m_neighbors.size() < 2) // NOT an intersection
				return;

			// Calc new direction aiming towards target
			glm::vec2 targetPos{ m_targetObj->GetWorldPosition() };
			glm::vec2 ownPos{ GetGameObject()->GetWorldPosition() };

			int bestIdx = -1;
			float bestDist = FLT_MAX;

			for (int neighborIdx : m_neighbors) // Choose closest neighbor to target to walk towards
			{
				glm::vec2 neighborPos = Graph::GetInstance().GetWorldPos(neighborIdx);
				float dist = glm::length(targetPos - neighborPos);
				if (dist < bestDist)
				{ 
					bestDist = dist;
					bestIdx = neighborIdx;
				}
			}

			if (bestIdx != -1)
			{
				glm::vec2 neighborPos = Graph::GetInstance().GetWorldPos(bestIdx);
				glm::vec2 ownGridPos = Graph::GetInstance().GetWorldPos(m_gridIdx);
				glm::vec2 diff = neighborPos - ownGridPos;

				if (abs(diff.x) > abs(diff.y))
				{
					// Horizonal
					if (diff.x > 0)
					{
						m_nextDir = glm::vec2{ 1, 0 };
						m_dir = Direction::right;
						std::cout << "right\n";
					}
					else
					{
						m_nextDir = glm::vec2{ -1, 0 };
						m_dir = Direction::left;
						std::cout << "left\n";
					}
				}
				else
				{
					// Vertical
					if (diff.y < 0)
					{
						m_nextDir = glm::vec2{ 0, -1 };
						m_dir = Direction::up;
						std::cout << "up\n";
					}
					else
					{
						m_nextDir = glm::vec2{ 0, 1 };
						m_dir = Direction::down;
						std::cout << "down\n";
						
					}
				}
			}
		}
	};
}