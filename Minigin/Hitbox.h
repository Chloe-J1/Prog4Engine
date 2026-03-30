#pragma once
#include "Component.h"
#include <glm/glm.hpp>
namespace dae
{
	class Hitbox : public Component
	{
	public:
		Hitbox(GameObject* gameObject, int width, int height);

		bool IsHit(const Hitbox& other);
		glm::vec2 GetMin() const;
		glm::vec2 GetMax() const;

	private:
		int m_width;
		int m_height;

	};
}
