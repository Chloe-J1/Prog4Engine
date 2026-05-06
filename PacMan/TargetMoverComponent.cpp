#include "TargetMoverComponent.h"
#include <iostream>
#include "../Minigin/GameObject.h"
#include "../Minigin/SpriteComponent.h"

pacman::TargetMoverComponent::TargetMoverComponent(dae::GameObject* owner, dae::GameObject* targetObj):
	Component(owner),
	m_targetObj(targetObj),
	m_spriteWidth{GetGameObject()->GetComponent<dae::SpriteComponent>()->GetWidth()},
	m_spriteHeight{GetGameObject()->GetComponent<dae::SpriteComponent>()->GetHeight()},
	m_graph{Graph::GetInstance()}
{
}


void pacman::TargetMoverComponent::MoveFrontTarget(float elapsedSec)
{
	if (IsInNewCell())
	{
		const float distance{ 100.f };
		m_targetPos = m_targetObj->GetWorldPosition();
		m_targetPos += m_nextDir * distance;
		ChangeDirection(false);
	}

	GetGameObject()->AddLocalPosition(m_nextDir * m_moveSpeed * elapsedSec);
}

void pacman::TargetMoverComponent::MoveAwayTarget(float elapsedSec)
{
	if (IsInNewCell())
	{
		m_targetPos = m_targetObj->GetWorldPosition();
		ChangeDirection(true);
	}

	GetGameObject()->AddLocalPosition(m_nextDir * m_moveSpeed * elapsedSec);
}

void pacman::TargetMoverComponent::MoveToTarget(float elapsedSec)
{
	if (IsInNewCell())
	{
		m_targetPos = m_targetObj->GetWorldPosition();
		ChangeDirection(false);
	}

	GetGameObject()->AddLocalPosition(m_nextDir * m_moveSpeed * elapsedSec);
}

void pacman::TargetMoverComponent::ChangeDirection(bool isMovingAway)
{
	std::cout << "gridIdx: " << m_gridIdx << " exists: " << m_graph.HasIndex(m_gridIdx) << "\n";
	if (m_graph.HasIndex(m_gridIdx) == false) return;
	m_neighbors = m_graph.GetNeighbors(m_gridIdx);
	if (m_neighbors.empty())
		return;

	if (m_neighbors.size() == 1) // Dead end
	{
		m_nextDir *= -1;
	}

	glm::vec2 ownPos{ GetGameObject()->GetWorldPosition()};

	int bestIdx = -1;
	if (not isMovingAway)
	{
		float bestDist = FLT_MAX;

		for (int neighborIdx : m_neighbors) // Choose closest neighbor to target to walk towards
		{
			glm::vec2 neighborPos = Graph::GetInstance().GetWorldPos(neighborIdx);
			float dist = glm::length(m_targetPos - neighborPos);
			if (dist < bestDist)
			{
				bestDist = dist;
				bestIdx = neighborIdx;
			}
		}
	}
	else
	{
		float bestDist = FLT_MIN;

		for (int neighborIdx : m_neighbors) // Choose furthest neighbor to target to walk towards
		{
			glm::vec2 neighborPos = Graph::GetInstance().GetWorldPos(neighborIdx);
			float dist = glm::length(m_targetPos - neighborPos);
			if (dist > bestDist)
			{
				bestDist = dist;
				bestIdx = neighborIdx;
			}
		}
	}


	

	if (bestIdx != -1)
	{
		std::cout << "Best Idx: " << bestIdx << "\n";
		glm::vec2 neighborPos = m_graph.GetWorldPos(bestIdx);
		glm::vec2 ownGridPos = m_graph.GetWorldPos(m_gridIdx);
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

bool pacman::TargetMoverComponent::IsInNewCell()
{
	const float halfSpriteWidth{ m_spriteWidth / 2.f };
	const float halfSpriteHeight{ m_spriteHeight / 2.f };
	glm::vec2 centerPos{ GetGameObject()->GetWorldPosition() };
	centerPos.x += halfSpriteWidth;
	centerPos.y += halfSpriteHeight;
	glm::vec2 furthestPos{ centerPos };
	switch (m_dir)
	{
	case pacman::Direction::right:
		furthestPos.x -= halfSpriteWidth;
		break;
	case pacman::Direction::left:
		furthestPos.x += halfSpriteWidth;
		break;
	case pacman::Direction::up:
		furthestPos.y += halfSpriteHeight;
		break;
	case pacman::Direction::down:
		furthestPos.y -= halfSpriteHeight;
		break;
	}

	int newGridIdx{ Graph::GetInstance().GetGridIdx(furthestPos) };
	if (newGridIdx != m_gridIdx)
	{
		m_gridIdx = newGridIdx;
		return true;
	}
	return false;
}
