#include "PlayerMovement.h"
#include "../Minigin/GameObject.h"
#include "WindowConfig.h"
#include "SpriteComponent.h"
#include "../Minigin/InputManager.h"
#include "Commands.h"
#include <memory>
#include "Graph.h"
#include "../Minigin/GameObject.h"

pacman::PlayerMovement::PlayerMovement(dae::GameObject* owner, bool usesKeyboard, bool usesController, int ctrlIdx) :
	Component(owner),
	m_speed{ 100.f },
	m_wWidth{ dae::WindowConfig::GetInstance().GetWidth() },
	m_wHeight{ dae::WindowConfig::GetInstance().GetHeight() },
	m_usesKeyboard{ usesKeyboard },
	m_usesController{ usesController },
	m_ctrlIdx{ ctrlIdx },
	m_previousIdx{-1}
{
	m_playerWidth = GetGameObject()->GetComponent<dae::SpriteComponent>()->GetWidth();
	m_playerHeight = GetGameObject()->GetComponent<dae::SpriteComponent>()->GetHeight();
	m_graph = &Graph::GetInstance();
	m_currIdx = m_graph->GetGridIdx(GetGameObject()->GetWorldPosition());

	// Input bindings
	if (usesController)
	{
		dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Right, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(1, 0), this), m_ctrlIdx); // right
		dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Left, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(-1, 0), this), m_ctrlIdx); // left
		dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(0, -1), this), m_ctrlIdx); // up
		dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(0, 1), this), m_ctrlIdx); // down
	}
	if(usesKeyboard)
	{
		dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_D, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(1, 0), this)); // right
		dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_A, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(-1, 0), this)); // left
		dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_W, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(0, -1), this)); // up
		dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_S, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::Move>(GetGameObject(), glm::vec2(0, 1), this)); // down
	}
}

pacman::PlayerMovement::~PlayerMovement()
{
	if (m_usesController)
	{
		dae::InputManager::GetInstance().UnbindCommand(dae::Input::DPad_Right, dae::TriggerEvent::PressedThisFrame, m_ctrlIdx); // right
		dae::InputManager::GetInstance().UnbindCommand(dae::Input::DPad_Left, dae::TriggerEvent::PressedThisFrame, m_ctrlIdx); // left
		dae::InputManager::GetInstance().UnbindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, m_ctrlIdx); // up
		dae::InputManager::GetInstance().UnbindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, m_ctrlIdx); // down

	}
	if(m_usesKeyboard)
	{
		dae::InputManager::GetInstance().UnbindCommand(SDL_SCANCODE_D, dae::TriggerEvent::Hold); // right
		dae::InputManager::GetInstance().UnbindCommand(SDL_SCANCODE_A, dae::TriggerEvent::Hold); // left
		dae::InputManager::GetInstance().UnbindCommand(SDL_SCANCODE_W, dae::TriggerEvent::Hold); // up
		dae::InputManager::GetInstance().UnbindCommand(SDL_SCANCODE_S, dae::TriggerEvent::Hold); // down
	}
}

void pacman::PlayerMovement::ChangeDirection(const glm::vec2& direction)
{
	if (m_graph->HasNeighborInDirection(m_graph->GetGridIdx(GetCenterPos()), direction))
	{
		m_currDirection = direction;
		m_previousIdx = -1;
		SnapToCell(m_graph->GetGridIdx(GetCenterPos()), direction);
	}
	else
	{
		m_desiredDirection = direction;
	}
}

void pacman::PlayerMovement::Update(float elapsedSec)
{
	int currGridIdx{ m_graph->GetGridIdx(GetCenterPos()) };
	if (m_previousIdx != -1 && m_previousIdx != currGridIdx)
	{
		if (m_graph->HasNeighborInDirection(currGridIdx, m_desiredDirection))
		{
			m_currDirection = m_desiredDirection;
			m_previousIdx = -1;
			SnapToCell(currGridIdx, m_currDirection);
		}
	}

	//m_oldPos = GetGameObject()->GetWorldPosition();
	GetGameObject()->AddLocalPosition(m_currDirection * m_speed * elapsedSec);


	WarpTunnels();
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
