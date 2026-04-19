#include "PlayerMovement.h"
#include "../Minigin/GameObject.h"
#include "WindowConfig.h"
#include "SpriteComponent.h"
#include "../Minigin/InputManager.h"
#include "Commands.h"
#include <memory>

pacman::PlayerMovement::PlayerMovement(dae::GameObject* owner, bool usesKeyboard, bool usesController, int ctrlIdx) :
	Component(owner),
	m_speed{100.f},
	m_wWidth{ dae::WindowConfig::GetInstance().GetWidth() },
	m_wHeight{ dae::WindowConfig::GetInstance().GetHeight() },
	m_usesKeyboard{ usesKeyboard },
	m_usesController{ usesController },
	m_ctrlIdx{ctrlIdx}
{
	m_playerWidth = GetGameObject()->GetComponent<dae::SpriteComponent>()->GetWidth();
	m_playerHeight = GetGameObject()->GetComponent<dae::SpriteComponent>()->GetHeight();

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

void pacman::PlayerMovement::Move(const glm::vec2& direction)
{
	m_currDirection = direction;
}

void pacman::PlayerMovement::OnCollision(dae::GameObject* other)
{
	if (other->GetLayer() == "Obstacle")
	{
		GetGameObject()->SetLocalPosition(m_oldPos.x, m_oldPos.y);
		m_currDirection = glm::vec2{ 0,0 };
	}
	
}

void pacman::PlayerMovement::Update(float elapsedSec)
{
	m_oldPos = GetGameObject()->GetWorldPosition();
	GetGameObject()->AddLocalPosition(m_currDirection * m_speed * elapsedSec);

	//Warp tunnels
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
