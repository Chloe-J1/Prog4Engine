#include "MoveComponent.h"
#include "GameObject.h"
#include <iostream>

dae::MoveComponent::MoveComponent(GameObject* owner, float speed):
	Component(owner),
	m_speed{speed}
{
}

void dae::MoveComponent::Move(const glm::vec2& direction)
{
	GetGameObject()->AddLocalPosition(direction * m_speed);
}
