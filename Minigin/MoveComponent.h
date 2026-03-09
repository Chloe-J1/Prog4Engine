#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class MoveComponent final : public Component
	{
	public:
		MoveComponent(GameObject* owner, float speed);
		virtual ~MoveComponent() = default;
		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent& operator=(MoveComponent&& other) = delete;

		void Move(const glm::vec2& direction);

	private:
		float m_speed;
	};
}
