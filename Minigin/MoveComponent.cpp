#include "MoveComponent.h"
#include "GameObject.h"
#include <iostream>

dae::MoveComponent::MoveComponent(GameObject* owner, float speed):
	Component(owner),
	m_speed{speed}
{
}

void dae::MoveComponent::Move(const glm::vec2& direction, float elapsedSec)
{
	GetGameObject()->AddLocalPosition(direction * m_speed * elapsedSec);
}
