#include "TargetMoverComponent.h"
#include <algorithm>
#include "../Minigin/GameObject.h"
#include "../Minigin/SpriteComponent.h"
#include <queue>
#include <iostream>
#include "../Minigin/DebugDraw.h"

pacman::TargetMoverComponent::TargetMoverComponent(dae::GameObject* owner):
	Component(owner),
	m_spriteWidth{GetGameObject()->GetComponent<dae::SpriteComponent>()->GetWidth()},
	m_spriteHeight{GetGameObject()->GetComponent<dae::SpriteComponent>()->GetHeight()},
	m_graph{Graph::GetInstance()}
{
}


void pacman::TargetMoverComponent::MoveFrontTarget(float elapsedSec)
{
	if (IsInNewCell() && m_targetObj->GetIsAlive())
	{
		const float distance{ 100.f };
		m_targetPos = m_targetObj->GetWorldPosition();
		m_targetPos += m_nextDir * distance;
		ChangeDirection(false);
	}

	Move(elapsedSec);
}

bool pacman::TargetMoverComponent::MoveToCell(int gridIdx, float elapsedSec)
{
	if (IsInNewCell() && m_targetObj->GetIsAlive())
	{
		if (m_gridIdx == gridIdx)
		{
			return true;
		}
		m_targetPos = m_graph.GetWorldPos(gridIdx);
		ChangeDirection(false);
	}

	Move(elapsedSec);
	return false;
}


void pacman::TargetMoverComponent::MoveAwayTarget(float elapsedSec)
{
	if (IsInNewCell() && m_targetObj->GetIsAlive())
	{
		m_targetPos = m_targetObj->GetWorldPosition();
		ChangeDirection(true);
	}

	Move(elapsedSec);
}

void pacman::TargetMoverComponent::MoveToTarget(float elapsedSec)
{
	if (m_targetObj->GetIsAlive() == false) return;
	m_targetPos = m_targetObj->GetWorldPosition();
	if (IsInNewCell() || m_pathIdx == m_path.size())
	{
		m_path = FindPath(GetGameObject()->GetWorldPosition(), m_targetPos);
		m_pathIdx = 0;
	}
	FollowPath(elapsedSec);
	
	/*if (IsInNewCell() && m_targetObj->GetIsAlive())
	{
		m_targetPos = m_targetObj->GetWorldPosition();
		ChangeDirection(false);
	}

	Move(elapsedSec);*/
}

void pacman::TargetMoverComponent::SetTargetObj(dae::GameObject* newTarget)
{
	if (newTarget == nullptr) return;
	m_targetObj = newTarget;
}

void pacman::TargetMoverComponent::Render() const
{
	for (const auto& square : m_path)
	{
		dae::DebugDraw::GetInstance().SetColor(0, 255, 0);
		dae::DebugDraw::GetInstance().DrawRect(square, 24, 24);
	}
}


void pacman::TargetMoverComponent::ChangeDirection(bool isMovingAway)
{
	//std::cout << "gridIdx: " << m_gridIdx << " exists: " << m_graph.HasIndex(m_gridIdx) << "\n";
	if (m_graph.HasIndex(m_gridIdx) == false) return;
	m_neighbors = m_graph.GetNeighbors(m_gridIdx);
	if (m_neighbors.empty())
		return;

	if (m_neighbors.size() == 1) // Dead end
	{
		m_nextDir *= -1;
	}

	glm::vec2 ownPos{ GetGameObject()->GetWorldPosition()};
	glm::vec2 ownGridPos = m_graph.GetWorldPos(m_gridIdx);
	
	int bestIdx = -1;
	if (not isMovingAway)
	{
		auto chosenItr = std::ranges::min_element(m_neighbors, {}, [&](int neigborIdx) {
			glm::vec2 neighborPos{ Graph::GetInstance().GetWorldPos(neigborIdx) };
			return glm::length(m_targetPos - neighborPos);
		});
		
		if (chosenItr != m_neighbors.end())
		{
			bestIdx = *chosenItr;
		}
	}
	else
	{
		auto chosenItr = std::ranges::max_element(m_neighbors, {}, [&](int neigborIdx) {
			glm::vec2 neighborPos{ Graph::GetInstance().GetWorldPos(neigborIdx) };
			return glm::length(m_targetPos - neighborPos);
			});
		if (chosenItr != m_neighbors.end())
		{
			bestIdx = *chosenItr;
		}
	}

	
	if (bestIdx != -1)
	{
		//std::cout << "Best Idx: " << bestIdx << "\n";
		glm::vec2 neighborPos = m_graph.GetWorldPos(bestIdx);
		ownGridPos = m_graph.GetWorldPos(m_gridIdx);
		glm::vec2 diff = neighborPos - ownGridPos;

		if (abs(diff.x) > abs(diff.y))
		{
			// Horizonal
			if (diff.x > 0)
			{
				m_nextDir = glm::vec2{ 1, 0 };
			}
			else
			{
				m_nextDir = glm::vec2{ -1, 0 };
			}
		}
		else
		{
			// Vertical
			if (diff.y < 0)
			{
				m_nextDir = glm::vec2{ 0, -1 };
			}
			else
			{
				m_nextDir = glm::vec2{ 0, 1 };
			}
		}
	}
}

bool pacman::TargetMoverComponent::IsTargetInNewCell()
{
	int newGridIdx{ m_graph.GetGridIdx(m_targetObj->GetWorldPosition()) };
	if (newGridIdx != m_targetGridIdx)
	{
		m_targetGridIdx = newGridIdx;
		return true;
	}
	return false;
}

bool pacman::TargetMoverComponent::IsInNewCell()
{
	const float halfSpriteWidth{ m_spriteWidth / 2.f };
	const float halfSpriteHeight{ m_spriteHeight / 2.f };
	glm::vec2 centerPos{ GetGameObject()->GetWorldPosition() };
	centerPos.x += halfSpriteWidth;
	centerPos.y += halfSpriteHeight;

	glm::vec2 furthestPos{ centerPos - m_nextDir * glm::vec2{halfSpriteWidth, halfSpriteHeight} };

	int newGridIdx{ Graph::GetInstance().GetGridIdx(furthestPos) };
	if (newGridIdx != m_gridIdx)
	{
		m_gridIdx = newGridIdx;
		return true;
	}
	return false;
}

void pacman::TargetMoverComponent::Move(float elapsedSec)
{
	GetGameObject()->AddLocalPosition(m_nextDir * m_moveSpeed * elapsedSec);
}

// BFS
//********

std::vector<glm::vec2> pacman::TargetMoverComponent::FindPath(const glm::vec2& startPos, const glm::vec2& destinationPos) const
{
	int nodeIdx{ m_graph.GetGridIdx(startPos) };
	int destIdx{ m_graph.GetGridIdx(destinationPos) };

	if (!m_graph.HasIndex(nodeIdx) || !m_graph.HasIndex(destIdx))
		return {};

	std::vector<glm::vec2> path{};
	std::unordered_set<int> visited; // Nodes for which the neighbors need to be checked next 
	std::unordered_map<int, int> parent; // Nodes that have been checked 
	std::queue<int> queue;

	queue.push(nodeIdx);
	visited.insert(m_graph.GetGridIdx(startPos));

	while (!queue.empty())
	{
		nodeIdx = queue.front();
		queue.pop();


		if (nodeIdx == destIdx)
			return ReconstructPath(parent, m_graph.GetGridIdx(startPos), destIdx);

		for (int neighbor : m_graph.GetNeighbors(nodeIdx))
		{
			if (visited.contains(neighbor) == false)
			{
				visited.insert(neighbor);
				parent[neighbor] = nodeIdx;
				queue.push(neighbor);
			}

		}
	}

	return path; // no path found
}

std::vector<glm::vec2> pacman::TargetMoverComponent::ReconstructPath(std::unordered_map<int, int>& parentMap, int startIdx, int destIdx) const
{
	std::vector<glm::vec2> path;
	int currentIdx = destIdx;

	while (currentIdx != startIdx)
	{
		path.push_back(m_graph.GetWorldPos(currentIdx));

		auto it = parentMap.find(currentIdx);
		if (it == parentMap.end())
			return {};

		currentIdx = it->second;
	}

	path.push_back(m_graph.GetWorldPos(startIdx));
	std::ranges::reverse(path.begin(), path.end());

	return path;
}

void pacman::TargetMoverComponent::FollowPath(float elapsedSec)
{
	if (m_path.empty() || m_pathIdx >= m_path.size()) return;

	glm::vec2 direction = m_path[m_pathIdx] - glm::vec2{ GetGameObject()->GetWorldPosition() };
	float distance = glm::length(direction);

	const float threshold = 1.f;
	if (distance <= threshold)
	{
		// Snap onto waypoint
		glm::vec2 correction = m_path[m_pathIdx] - glm::vec2{ GetGameObject()->GetWorldPosition() };
		GetGameObject()->AddLocalPosition(correction);

		++m_pathIdx;

		if (m_pathIdx >= m_path.size())
			return;
	}
	else
	{
		glm::vec2 currentPos = GetGameObject()->GetWorldPosition();
		glm::vec2 diff = m_path[m_pathIdx] - currentPos;

		if (abs(diff.x) > 1.f)
		{
			m_nextDir =
			{
				(diff.x > 0.f) ? 1.f : -1.f,
				0.f
			};
		}
		else if (abs(diff.y) > 1.f)
		{
			m_nextDir =
			{
				0.f,
				(diff.y > 0.f) ? 1.f : -1.f
			};
		}

		GetGameObject()->AddLocalPosition(m_nextDir * m_moveSpeed * elapsedSec);
	}
}