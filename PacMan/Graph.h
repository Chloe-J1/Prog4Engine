#pragma once
#include "../Minigin/Singleton.h"
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <glm/glm.hpp>
namespace pacman
{
	class Graph final : public dae::Singleton<Graph>
	{
	public:
		Graph();
		int GetGridIdx(const glm::vec2& pos) const;
		const std::vector<int>& GetNeighbors(int gridIdx) const;
		const std::unordered_map<int, std::vector<int>>& GetGraph() const;
		void SetNeighbors(const std::unordered_set<int>& indices);
		glm::vec2 GetWorldPos(int gridIdx) const;
		bool HasIndex(int gridIdx) const;
		bool HasNeighbor(int gridIdx, int neighborIdx) const;
		bool HasNeighborInDirection(int gridIdx, const glm::vec2& direction) const;

		int GetNrCols() const;
		int GetNrRows() const;
		int GetCellSize() const;
	private:
		std::unordered_map<int, std::vector<int>> m_graph;
		const int m_gridWidth;
		const int m_gridHeight;
		const int m_cellsize{ 24 };
		const int m_nrCols;
		const int m_nrRows;
	};
}