#include "PlayerMovement.h"
#include "../Minigin/GameObject.h"
#include "WindowConfig.h"
#include "SpriteComponent.h"
#include "Commands.h"
#include <memory>
#include "Graph.h"
#include "../Minigin/DebugDraw.h"
#include <iostream>

pacman::PlayerMovement::PlayerMovement(dae::GameObject* owner, bool usesKeyboard, bool usesController, int ctrlIdx) :
	Component(owner),
	m_speed{ 100.f },
	m_wWidth{ dae::WindowConfig::GetInstance().GetWidth() },
	m_wHeight{ dae::WindowConfig::GetInstance().GetHeight() },
	m_usesKeyboard{ usesKeyboard },
	m_usesController{ usesController },
	m_ctrlIdx{ ctrlIdx },
	m_inputManager{&dae::InputManager::GetInstance()}
{
	m_spriteComp = GetGameObject()->GetComponent<dae::SpriteComponent>();
	m_playerWidth = m_spriteComp->GetWidth();
	m_playerHeight = m_spriteComp->GetHeight();
	m_graph = &Graph::GetInstance();

	// Input bindings
	if (usesController)
	{
		m_inputManager->BindCommand(dae::Input::DPad_Right, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(1, 0), this), m_ctrlIdx); // right
		m_inputManager->BindCommand(dae::Input::DPad_Left, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(-1, 0), this), m_ctrlIdx); // left
		m_inputManager->BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(0, -1), this), m_ctrlIdx); // up
		m_inputManager->BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(0, 1), this), m_ctrlIdx); // down
	}
	if(usesKeyboard)
	{
		m_inputManager->BindCommand(SDL_SCANCODE_D, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(1, 0), this)); // right
		m_inputManager->BindCommand(SDL_SCANCODE_A, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(-1, 0), this)); // left
		m_inputManager->BindCommand(SDL_SCANCODE_W, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(0, -1), this)); // up
		m_inputManager->BindCommand(SDL_SCANCODE_S, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(0, 1), this)); // down
	}
}

pacman::PlayerMovement::~PlayerMovement()
{
	if (m_usesController)
	{
		m_inputManager->UnbindCommand(dae::Input::DPad_Right, dae::TriggerEvent::PressedThisFrame, m_ctrlIdx); // right
		m_inputManager->UnbindCommand(dae::Input::DPad_Left, dae::TriggerEvent::PressedThisFrame, m_ctrlIdx); // left
		m_inputManager->UnbindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, m_ctrlIdx); // up
		m_inputManager->UnbindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, m_ctrlIdx); // down

	}
	if(m_usesKeyboard)
	{
		m_inputManager->UnbindCommand(SDL_SCANCODE_D, dae::TriggerEvent::PressedThisFrame); // right
		m_inputManager->UnbindCommand(SDL_SCANCODE_A, dae::TriggerEvent::PressedThisFrame); // left
		m_inputManager->UnbindCommand(SDL_SCANCODE_W, dae::TriggerEvent::PressedThisFrame); // up
		m_inputManager->UnbindCommand(SDL_SCANCODE_S, dae::TriggerEvent::PressedThisFrame); // down
	}
}

void pacman::PlayerMovement::ChangeDirection(const glm::vec2& direction)
{
	if (direction == m_currDirection) return;
	int gridIdx{ m_graph->GetGridIdx(GetCenterPos()) };
	if (m_graph->HasNeighborInDirection(gridIdx, direction))
	{
		m_currDirection = direction;
		SnapToCell(gridIdx, direction);
		ChangeAnimation(direction);
	}
}

void pacman::PlayerMovement::Update(float elapsedSec)
{
	m_oldPos = GetGameObject()->GetWorldPosition();
	GetGameObject()->AddLocalPosition(m_currDirection * m_speed * elapsedSec);
	WarpTunnels();
	WallCheck();
}

void pacman::PlayerMovement::Render() const
{
	const int size{ 3 };
	dae::DebugDraw::GetInstance().SetColor(255,0,0);
	dae::DebugDraw::GetInstance().FillRect(m_furthestPos, size, size);
}


glm::vec2 pacman::PlayerMovement::GetCenterPos() const
{
	glm::vec2 center{ GetGameObject()->GetWorldPosition() };
	center.x += m_playerWidth / 2.f;
	center.y += m_playerHeight / 2.f;
	return center;
}

void pacman::PlayerMovement::SnapToCell(int gridIdx, const glm::vec2& newDir)
{
	glm::vec2 cellPos = m_graph->GetWorldPos(gridIdx);

	if (newDir.x != 0)
		GetGameObject()->SetLocalPosition(cellPos);
	if (newDir.y != 0)
		GetGameObject()->SetLocalPosition(cellPos);
}
void pacman::PlayerMovement::WarpTunnels()
{
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

void pacman::PlayerMovement::WallCheck()
{
	const float halfSpriteWidth{ m_playerWidth / 2.f };
	const float halfSpriteHeight{ m_playerHeight / 2.f };
	glm::vec2 centerPos{ GetGameObject()->GetWorldPosition() };
	centerPos.x += halfSpriteWidth;
	centerPos.y += halfSpriteHeight;

	m_furthestPos = centerPos + m_currDirection * glm::vec2{halfSpriteWidth, halfSpriteHeight};
	const float epsilon{ 3.f };
	if (m_furthestPos.x < epsilon || m_furthestPos.x > m_wWidth - epsilon || m_furthestPos.y < epsilon || m_furthestPos.y > m_wHeight - epsilon) return; // Outside of screen = use warp tunnels

	int newGridIdx{ Graph::GetInstance().GetGridIdx(m_furthestPos) };
	if (not m_graph->HasIndex(newGridIdx))
	{
		GetGameObject()->SetLocalPosition(m_oldPos);
	}
}

void pacman::PlayerMovement::ChangeAnimation(const glm::vec2& direction)
{
	if (direction.x == 1) // right
	{
		m_spriteComp->SetRow(0);
	}
	else if (direction.x == -1) // left
	{
		m_spriteComp->SetRow(1);
	}
	else if (direction.y == -1) // up
	{
		m_spriteComp->SetRow(2);
	}
	else  // down
	{
		m_spriteComp->SetRow(3);
	}
}
