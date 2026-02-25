#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <iostream>
namespace dae
{
	class RotationComponent final : public Component
	{
	public:
		RotationComponent(GameObject* owner, float distance, bool isClockwise = true):
			Component::Component(owner),
			m_radius{distance},
			m_isClockwise{isClockwise}
		{
		}
		~RotationComponent() = default;
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;

	private:
		float m_currAngle{ 0.f };
		float m_stepAngle{ 5.f };
		const float m_radius;
		bool m_isClockwise;
	};
}
