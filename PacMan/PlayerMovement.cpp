#include "PlayerMovement.h"
#include "../Minigin/GameObject.h"
#include <iostream>
pacman::PlayerMovement::PlayerMovement(dae::GameObject* owner) :
	Component(owner)
{
}

void pacman::PlayerMovement::Move(float speed, const glm::vec2& direction, float elaspedSec)
{
	m_oldPos = GetGameObject()->GetWorldPosition();
	GetGameObject()->AddLocalPosition(speed * direction * elaspedSec);
}

void pacman::PlayerMovement::OnCollision(dae::GameObject* other)
{
	if (other->GetLayer() == "Obstacle")
	{
		GetGameObject()->SetLocalPosition(m_oldPos.x, m_oldPos.y);
	}
}
