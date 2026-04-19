#pragma once
#include "../Minigin/Component.h"
#include <glm/glm.hpp>

namespace pacman
{
	class GameObject;
	class PlayerMovement final : public dae::Component
	{
	public:
		explicit PlayerMovement(dae::GameObject* owner, bool usesKeyboard, bool usesController, int ctrlIdx = 0);
		~PlayerMovement();
		PlayerMovement(const PlayerMovement& other) = delete;
		PlayerMovement(PlayerMovement&& other) = delete;
		PlayerMovement& operator=(const PlayerMovement& other) = delete;
		PlayerMovement& operator=(PlayerMovement&& other) = delete;
		

		void Move(const glm::vec2& direction);
		virtual void OnCollision(dae::GameObject* other) override;
		virtual void Update(float elapsedSec) override;

	private:
		glm::vec2 m_oldPos{};
		glm::vec2 m_currDirection{};
		const float m_speed;
		const int m_wWidth;
		const int m_wHeight;
		float m_playerWidth;
		float m_playerHeight;

		bool m_usesKeyboard;
		bool m_usesController;
		int m_ctrlIdx;
	};
}
