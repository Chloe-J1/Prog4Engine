#pragma once
#include "../Minigin/Component.h"
#include <glm/glm.hpp>
namespace pacman
{
	class dae::GameObject;
	class PlayerMovement final : public dae::Component
	{
	public:
		explicit PlayerMovement(dae::GameObject* owner);

		void Move(const glm::vec2& direction);
		virtual void OnCollision(dae::GameObject* other) override;
		virtual void Update(float elapsedSec) override;
	private:
		glm::vec2 m_oldPos{};
		glm::vec2 m_currDirection{};
		const float m_speed;
	};
}
