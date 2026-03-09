#include "MoveComponent.h"
#include "GameObject.h"
#include <iostream>

dae::MoveComponent::MoveComponent(GameObject* owner):
	Component(owner)
{
}

void dae::MoveComponent::Move(float speed, glm::vec3 direction)
{
	std::cout << "JUMP\n";
}
