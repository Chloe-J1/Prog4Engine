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

		void Move(float speed, const glm::vec2& direction, float elaspedSec);
		virtual void OnCollision(dae::GameObject* other) override;

	private:
		glm::vec2 m_oldPos;
	};
}
