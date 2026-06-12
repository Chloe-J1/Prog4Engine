#pragma once
#include "../Minigin/Component.h"
#include <vector>
#include <glm/glm.hpp>
#include "Graph.h"
#include "../Minigin/EventQueue.h"
#include "../Minigin/Draw.h"

namespace pacman
{
	class TargetMoverComponent final : public dae::Component
	{
	public:
		explicit TargetMoverComponent(dae::GameObject* owner);
		void MoveToTarget(float elapsedSec);
		void MoveAwayTarget(float elapsedSec);
		void MoveFrontTarget(float elapsedSec);
		bool MoveToCell(int gridIdx, float elapsedSec);
		void CalcPath(int gridIdx);
		void Wander(float elapsedSec);
		
		void SetTargetObj(dae::GameObject* newTarget);
	private:
		float m_moveSpeed{ 50.f };
		dae::GameObject* m_targetObj{};
		glm::vec2 m_targetPos{};
		glm::vec2 m_nextDir{ 0,-1 };
		int m_gridIdx{};
		int m_cellsize;
		std::vector<int> m_neighbors;
		const float m_spriteWidth;
		const float m_spriteHeight;
		Graph& m_graph;
		int m_nrTilesMoved{};
		int m_wWidth;
		int m_wHeight;
		int m_nrCols;
		int m_nrRows;
		dae::GameObject* m_gameObject{ GetGameObject() };
		dae::EventQueue& m_eventQueue{ dae::EventQueue::GetInstance() };

		// BFS
		std::vector<glm::vec2> m_path;
		int m_pathIdx{ 0 };

		void Render() const;
		void FollowPath(float elapsedSec);
		std::vector<glm::vec2> FindPath(const glm::vec2& startPos, const glm::vec2& destinationPos) const;
		std::vector<glm::vec2> ReconstructPath(std::unordered_map<int, int>& parentMap, int startIdx, int destIdx) const;
		dae::Draw& m_drawHelper{ dae::Draw::GetInstance() };


		void ChangeDirection(bool isMovingAway);
		bool IsInNewCell();
		void Move(float elapsedSec);
		int GetRandomGridIdx() const;
		void CalcNextDir(const glm::vec2& difference);
	};
}