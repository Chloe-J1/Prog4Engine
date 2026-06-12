#include "TargetMoverComponent.h"
#include <algorithm>
#include "../Minigin/GameObject.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/WindowConfig.h"
#include "Events.h"


pacman::TargetMoverComponent::TargetMoverComponent(dae::GameObject* owner):
	Component(owner),
	m_spriteWidth{GetGameObject()->GetComponent<dae::SpriteComponent>()->GetWidth()},
	m_spriteHeight{GetGameObject()->GetComponent<dae::SpriteComponent>()->GetHeight()},
	m_graph{Graph::GetInstance()},
	m_wWidth{dae::WindowConfig::GetInstance().GetWidth()},
	m_wHeight{dae::WindowConfig::GetInstance().GetHeight()}
{
	m_cellsize = m_graph.GetCellSize();
	m_nrCols = m_graph.GetNrCols();
	m_nrRows = m_graph.GetNrRows();
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

bool pacman::TargetMoverComponent::MoveToCell(int, float elapsedSec)
{
	if (m_pathIdx >= (int)m_path.size())
	{
		m_path.clear();
		m_pathIdx = 0;
		return true;
	}
	FollowPath(elapsedSec);
	return false;
}

void pacman::TargetMoverComponent::CalcPath(int gridIdx)
{
	glm::vec2 centerPos = m_gameObject->GetWorldPosition();
	
	centerPos.x += m_spriteWidth / 2.f;
	centerPos.y += m_spriteHeight / 2.f;

	m_path = FindPath(centerPos, m_graph.GetWorldPos(gridIdx));
	m_pathIdx = 0;
}

// Wander changes the random target after moving X amount of tiles
void pacman::TargetMoverComponent::Wander(float elapsedSec)
{
	const int neededTilesMoved{ 10 };
	if (IsInNewCell())
	{
		++m_nrTilesMoved;
		if (m_nrTilesMoved >= neededTilesMoved)
		{
			m_targetPos = m_graph.GetWorldPos(GetRandomGridIdx());
		}
		ChangeDirection(false);
	}
	Move(elapsedSec);
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
	if (IsInNewCell() && m_targetObj->GetIsAlive())
	{
		m_targetPos = m_targetObj->GetWorldPosition();
		ChangeDirection(false);
	}

	Move(elapsedSec);
}

void pacman::TargetMoverComponent::SetTargetObj(dae::GameObject* newTarget)
{
	if (newTarget == nullptr) return;
	m_targetObj = newTarget;
}

void pacman::TargetMoverComponent::Render() const
{
#ifdef _DEBUG
	if (m_path.empty()) return;
	for (const auto& pos : m_path)
	{
		m_drawHelper.SetColor(0, 255, 0);
		m_drawHelper.DrawRect(pos, (float)m_cellsize, (float)m_cellsize);
	}
#endif // _DEBUG
}

bool pacman::TargetMoverComponent::IsInNewCell()
{
	const float halfSpriteWidth{ m_spriteWidth / 2.f };
	const float halfSpriteHeight{ m_spriteHeight / 2.f };
	glm::vec2 centerPos{ m_gameObject->GetWorldPosition() };
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

void pacman::TargetMoverComponent::FollowPath(float elapsedSec)
{
	if (m_path.empty() || m_pathIdx >= (int)m_path.size()) return;

	glm::vec2 direction = m_path[m_pathIdx] - glm::vec2{ m_gameObject->GetWorldPosition() };
	float distance = glm::length(direction);

	const float threshold = 1.f;
	if (distance <= threshold)
	{
		// Snap exact op waypoint
		glm::vec2 correction = m_path[m_pathIdx] - glm::vec2{ m_gameObject->GetWorldPosition() };
		m_gameObject->AddLocalPosition(correction);

		++m_pathIdx;

		if (m_pathIdx >= (int)m_path.size())
			return;
	}
	else
	{
		glm::vec2 currentPos = m_gameObject->GetWorldPosition();
		glm::vec2 diff = m_path[m_pathIdx] - currentPos;

		CalcNextDir(diff);
		Move(elapsedSec);
	}
}

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
	std::reverse(path.begin(), path.end());

	return path;
}

void pacman::TargetMoverComponent::ChangeDirection(bool isMovingAway)
{
	if (m_graph.HasIndex(m_gridIdx) == false) return;
	m_neighbors = m_graph.GetNeighbors(m_gridIdx);
	if (m_neighbors.empty())
		return;

	// Don't allow turning back
	glm::vec2 pos{ m_graph.GetWorldPos(m_gridIdx) };
	pos -= m_nextDir * float(m_cellsize);
	int behindIdx{m_graph.GetGridIdx(pos)};

	std::erase(m_neighbors, behindIdx);

	if (m_neighbors.empty()) // Dead end, allow turning back
	{
		m_neighbors.push_back(behindIdx);
	}


	int bestIdx = -1;
	auto projection = [&](int neighborIdx) {
		return glm::length(m_targetPos - m_graph.GetWorldPos(neighborIdx));
		};

	if (not isMovingAway)
	{
		auto chosenItr = std::ranges::min_element(m_neighbors, {}, projection);
		if (chosenItr != m_neighbors.end())
		{
			bestIdx = *chosenItr;
		}
	}
	else
	{
		auto chosenItr = std::ranges::max_element(m_neighbors, {}, projection);
		if (chosenItr != m_neighbors.end())
		{
			bestIdx = *chosenItr;
		}
	}

	if (bestIdx != -1)
	{
		glm::vec2 neighborPos = m_graph.GetWorldPos(bestIdx);
		glm::vec2 ownGridPos = m_graph.GetWorldPos(m_gridIdx);
		glm::vec2 diff = neighborPos - ownGridPos;
		CalcNextDir(diff);

		dae::Event e{ "DIRECTION_CHANGED" };
		e.arg = std::make_unique<pacman::DirectionChangedArg>(m_nextDir, GetGameObject());
		m_eventQueue.Invoke(std::move(e));
	}
}
void pacman::TargetMoverComponent::Move(float elapsedSec)
{
	GetGameObject()->AddLocalPosition(m_nextDir * m_moveSpeed * elapsedSec);
}

int pacman::TargetMoverComponent::GetRandomGridIdx() const
{
	int col = rand() % m_nrCols;
	int row = rand() % m_nrRows;

	return row * m_nrCols + col;
}

void pacman::TargetMoverComponent::CalcNextDir(const glm::vec2& difference)
{
	if (abs(difference.x) > abs(difference.y))
	{
		// Horizonal
		if (difference.x > 0)
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
		if (difference.y < 0)
		{
			m_nextDir = glm::vec2{ 0, -1 };
		}
		else
		{
			m_nextDir = glm::vec2{ 0, 1 };
		}
	}
}
