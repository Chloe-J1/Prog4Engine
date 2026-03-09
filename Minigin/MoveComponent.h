#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class MoveComponent final : public Component
	{
	public:
		MoveComponent(GameObject* owner);
		virtual ~MoveComponent() = default;
		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent& operator=(MoveComponent&& other) = delete;

		void Move(float speed, glm::vec3 direction);

	private:

	};
}
