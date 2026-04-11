#include "PlayerMovement.h"
#include "../Minigin/GameObject.h"
#include "WindowConfig.h"
#include "SpriteComponent.h"

pacman::PlayerMovement::PlayerMovement(dae::GameObject* owner) :
	Component(owner),
	m_speed{100.f},
	m_wWidth{ dae::WindowConfig::GetInstance().GetWidth() },
	m_wHeight{ dae::WindowConfig::GetInstance().GetHeight() }
{
	m_playerWidth = GetGameObject()->GetComponent<dae::SpriteComponent>()->GetWidth();
	m_playerHeight = GetGameObject()->GetComponent<dae::SpriteComponent>()->GetHeight();
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
	
	// TODO: clean this

	glm::vec3 pos{ GetGameObject()->GetTransform().GetWorldPosition() };
	if (pos.x < -m_playerWidth)
	{
		GetGameObject()->SetLocalPosition((float)m_wWidth, pos.y);
	}
	else if (pos.x > m_wWidth)
	{
		GetGameObject()->SetLocalPosition(-m_playerWidth, pos.y);
	}
	else if (pos.y < -m_playerHeight)
	{
		GetGameObject()->SetLocalPosition(pos.x, (float)m_wHeight);
	}
	else if (pos.y > m_wHeight)
	{
		GetGameObject()->SetLocalPosition(pos.x, -m_playerHeight);
	}
}
