#pragma once
#include "Component.h"
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

		void Jump();

	private:

	};
}
