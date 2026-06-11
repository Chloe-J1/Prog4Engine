#pragma once
#include "../Minigin/Component.h"
#include <glm/glm.hpp>
#include "../Minigin/InputManager.h"

namespace dae
{
	class SpriteComponent;
}

namespace pacman
{
	class Graph;
	class PlayerMovement final : public dae::Component
	{
	public:
		explicit PlayerMovement(dae::GameObject* owner, bool usesKeyboard, bool usesController, int ctrlIdx = 0);
		~PlayerMovement();
		PlayerMovement(const PlayerMovement& other) = delete;
		PlayerMovement(PlayerMovement&& other) = delete;
		PlayerMovement& operator=(const PlayerMovement& other) = delete;
		PlayerMovement& operator=(PlayerMovement&& other) = delete;
		

		void ChangeDirection(const glm::vec2& direction);
	private:
		const float m_speed;

		const int m_wWidth;
		const int m_wHeight;

		bool m_usesKeyboard;
		bool m_usesController;
		int m_ctrlIdx;
		Graph* m_graph;
		dae::SpriteComponent* m_spriteComp;
		dae::InputManager* m_inputManager;

		glm::vec2 m_oldPos{};
		glm::vec2 m_currDirection{};
		
		float m_playerWidth;
		float m_playerHeight;

		void Update(float elapsedSec);
		void WarpTunnels();
		glm::vec2 GetCenterPos() const;
		void SnapToCell(int gridIdx, const glm::vec2& newDir);
		void WallCheck();
	};
}
