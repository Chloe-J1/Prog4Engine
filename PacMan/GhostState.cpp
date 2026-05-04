#include "GhostState.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/GameObject.h"
#include "Ghost.h"
#include "Graph.h"
#include <iostream>

pacman::MoveTargetState::MoveTargetState(dae::GameObject* ghost, dae::GameObject* targetObj):
	m_ghost{ghost},
	m_targetObj{ targetObj }
{
}

// MOVE
pacman::GhostState* pacman::MoveTargetState::Update(float elapsedSec)
{
	MoveInDirection(elapsedSec);
	return nullptr;
}

void pacman::MoveTargetState::SetTarget(dae::GameObject* targetObj)
{
	m_targetObj = targetObj;
}

void pacman::MoveTargetState::MoveInDirection(float elapsedSec)
{
	const float spriteSize{ 24 };
	const float halfSpriteSize{ spriteSize / 2.f };
	glm::vec2 centerPos{ m_ghost->GetWorldPosition() };
	centerPos.x += halfSpriteSize;
	centerPos.y += halfSpriteSize;
	glm::vec2 furthestPos{ centerPos };
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

	m_ghost->AddLocalPosition(m_nextDir * m_moveSpeed * elapsedSec);
}

void pacman::MoveTargetState::ChangeDirection()
{
	std::cout << "gridIdx: " << m_gridIdx << " exists: " << Graph::GetInstance().HasIndex(m_gridIdx) << "\n";
	if (Graph::GetInstance().HasIndex(m_gridIdx) == false) return;
	m_neighbors = Graph::GetInstance().GetNeighbors(m_gridIdx);
	if (m_neighbors.empty())
		return;

	if (m_neighbors.size() == 1) // Dead end
	{
		m_nextDir *= -1;
	}

	// Calc new direction aiming towards target
	glm::vec2 targetPos{ m_targetObj->GetWorldPosition() };
	glm::vec2 ownPos{ m_ghost->GetWorldPosition() };

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
		std::cout << "Best Idx: " << bestIdx << "\n";
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



// CHASE
pacman::ChaseState::ChaseState(dae::GameObject* ghost, dae::SpriteComponent* spriteComp, dae::GameObject* targetObj):
	MoveTargetState(ghost, targetObj),
	m_spriteComp{spriteComp}
{
	if (m_spriteComp == nullptr)
		std::cerr << "Missing spritecomponent reference\n";
}

pacman::GhostState* pacman::ChaseState::Update(float elapsedSec)
{
	MoveTargetState::Update(elapsedSec);
	return nullptr;
}

void pacman::ChaseState::OnEnter()
{
	m_spriteComp->SetRow(0);
}

// DIZZIED
pacman::DizziedState::DizziedState(dae::GameObject* ghost, dae::SpriteComponent* spriteComp, dae::GameObject* targetObj) :
	MoveTargetState(ghost, targetObj),
	m_spriteComp{spriteComp}
{
	if (m_spriteComp == nullptr)
		std::cerr << "Missing spritecomponent reference\n";
}

pacman::GhostState* pacman::DizziedState::Update(float elapsedSec)
{
	MoveTargetState::Update(elapsedSec);
	// Code to return chase state if you are dizzied for too long
	return nullptr;
}

void pacman::DizziedState::OnEnter()
{
	m_spriteComp->SetRow(4);
}

// EYES
pacman::EyeState::EyeState(dae::SpriteComponent* spriteComp):
	m_spriteComp{spriteComp}
{
	if (m_spriteComp == nullptr)
		std::cerr << "Missing spritecomponent reference\n";
}

pacman::GhostState* pacman::EyeState::Update(float)
{
	return nullptr;
}

void pacman::EyeState::OnEnter()
{
}
