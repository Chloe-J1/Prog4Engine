#include "MoveComponent.h"
#include <iostream>

dae::MoveComponent::MoveComponent(GameObject* owner):
	Component(owner)
{
}

void dae::MoveComponent::Jump()
{
	std::cout << "JUMP\n";
}
