#include "PlayerMovement.h"
#include "../Minigin/GameObject.h"
#include <iostream>
pacman::PlayerMovement::PlayerMovement(dae::GameObject* owner) :
	Component(owner),
	m_speed{100.f}
{
}

void pacman::PlayerMovement::Move(const glm::vec2& direction)
{
	m_currDirection = direction;
}

void pacman::PlayerMovement::OnCollision(dae::GameObject* other)
{
	if (other->GetLayer() == "Obstacle")
	{
		GetGameObject()->SetLocalPosition(m_oldPos.x, m_oldPos.y);
		m_currDirection = { 0,0 };
	}
}

void pacman::PlayerMovement::Update(float elapsedSec)
{
	m_oldPos = GetGameObject()->GetWorldPosition();
	GetGameObject()->AddLocalPosition(m_currDirection * m_speed * elapsedSec);

}
