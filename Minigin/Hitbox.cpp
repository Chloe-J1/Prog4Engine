#include "Hitbox.h"
#include "GameObject.h"
#include "Event.h"
#include "EventQueue.h"
#include "CollisionManager.h"

#include <iostream>

dae::Hitbox::Hitbox(GameObject* gameObject, int width, int height):
	Component(gameObject),
	m_width{width},
	m_height{height}
{
	CollisionManager::GetInstance().AddHitbox(this);
}

dae::Hitbox::~Hitbox()
{
	CollisionManager::GetInstance().RemoveHitbox(this);
}

bool dae::Hitbox::IsHit(const Hitbox& other)
{
	glm::vec2 max{ this->GetMax() };
	glm::vec2 min{ this->GetMin()};
	glm::vec2 otherMax{ other.GetMax() };
	glm::vec2 otherMin{ other.GetMin() };

	// Check if the rectangles are separated on either axis
	if (max.x < otherMin.x || min.x > otherMax.x) return false;
	if (max.y < otherMin.y || min.y > otherMax.y) return false;

	// If they are not separated, they must overlap
	return true;
}

glm::vec2 dae::Hitbox::GetMin() const
{
	glm::vec2 worldPos = GetGameObject()->GetWorldPosition();
	return glm::vec2(worldPos.x, worldPos.y - m_height);
}

glm::vec2 dae::Hitbox::GetMax() const
{
	glm::vec2 worldPos = GetGameObject()->GetWorldPosition();
	return glm::vec2(worldPos.x + m_width, worldPos.y);
}
