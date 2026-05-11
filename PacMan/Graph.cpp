#include "Graph.h"
#include "../Minigin/WindowConfig.h"
#include <iostream>
#include <algorithm>

pacman::Graph::Graph() :
	m_gridWidth{ dae::WindowConfig::GetInstance().GetWidth() },
	m_gridHeight{ dae::WindowConfig::GetInstance().GetHeight() },
	m_nrCols{ m_gridWidth / m_cellsize },
	m_nrRows{ m_gridHeight / m_cellsize }
{
}

int pacman::Graph::GetGridIdx(const glm::vec2& pos) const
{
	return (int(pos.y / m_cellsize) * m_nrCols) + int(pos.x / m_cellsize);
}

const std::vector<int>& pacman::Graph::GetNeighbors(int gridIdx) const
{
	return m_graph.at(gridIdx);
}

const std::unordered_map<int, std::vector<int>>& pacman::Graph::GetGraph() const
{
	return m_graph;
}

void pacman::Graph::SetNeighbors(const std::unordered_set<int>& indices)
{
	std::cout << "SetNeighbors called with " << indices.size() << " indices\n";
	for (int index : indices)
		m_graph[index]; // Add keys of indices that are walkable

	for (int index : indices)
	{
		if (index % m_nrCols != 0)
		{
			int leftNeighbor = index - 1;
			if (indices.contains(leftNeighbor))
			{
				m_graph[index].push_back(leftNeighbor);
			}
		}

		if ((index + 1) % m_nrCols != 0)
		{
			int rightNeighbor = index + 1;
			if (indices.contains(rightNeighbor))
			{
				m_graph[index].push_back(rightNeighbor);
			}
		}

		int currRow = index / m_nrCols;
		int bottomNeighbor = index + m_nrCols;
		if (currRow != m_nrRows - 1)
		{
			if (indices.contains(bottomNeighbor))
			{
				m_graph[index].push_back(bottomNeighbor);
			}
		}

		int topNeighbor = index - m_nrCols;
		if (currRow != 0)
		{
			if (indices.contains(topNeighbor))
			{
				m_graph[index].push_back(topNeighbor);
			}
		}
	}
}

glm::vec2 pacman::Graph::GetWorldPos(int gridIdx) const
{
	int col = gridIdx % m_nrCols;
	int row = gridIdx / m_nrCols;
	glm::vec2 worldPos{ col * m_cellsize, row * m_cellsize };
	return worldPos;
}

bool pacman::Graph::HasIndex(int gridIdx) const
{
	return m_graph.contains(gridIdx);
}

bool pacman::Graph::HasNeighbor(int gridIdx, int neighborIdx) const
{
	if (HasIndex(gridIdx) == false) return false;
	const std::vector<int>& neighbors = m_graph.at(gridIdx);
	auto itr = std::find(neighbors.begin(), neighbors.end(), neighborIdx);
	if (itr != neighbors.end())
		return true;
	return false;
}

bool pacman::Graph::HasNeighborInDirection(int gridIdx, const glm::vec2& direction) const
{
	if (HasIndex(gridIdx) == false) return false;
	glm::vec2 neighborPos{ direction };
	neighborPos.x *= m_cellsize;
	neighborPos.y *= m_cellsize;
	neighborPos += GetWorldPos(gridIdx);

	int directionIdx{ GetGridIdx(neighborPos) };
	const std::vector<int>& neighbors = m_graph.at(gridIdx);

	if (std::find(neighbors.begin(), neighbors.end(), directionIdx) != neighbors.end())
	{
		return true;
	}
	return false;
}

int pacman::Graph::GetNrCols() const
{
	return m_nrCols;
}

int pacman::Graph::GetNrRows() const
{
	return m_nrRows;
}

int pacman::Graph::GetCellSize() const
{
	return m_cellsize;
}
