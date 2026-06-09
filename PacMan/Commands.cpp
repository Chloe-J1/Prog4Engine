#include "Commands.h"
#include "MenuManager.h"
#include "ButtonComponent.h"
#include "../Minigin/ServiceLocator.h"
#include "../Minigin/SoundSystem.h"
#include <memory>

// MOVE
//********
pacman::Move::Move(dae::GameObject* gameObject, const glm::vec2& direction, pacman::PlayerMovement* moveComp) :
	GameObjectCommand(gameObject),
	m_direction{ direction },
	m_moveComp(moveComp)
{
}
void pacman::Move::Execute()
{
	m_moveComp->ChangeDirection(m_direction);
}

// BUTTON SELECTION
//********
void pacman::NextButton::Execute()
{
	MenuManager::GetInstance().SelectNextButton();
}

void pacman::PreviousButton::Execute()
{
	MenuManager::GetInstance().SelectPreviousButton();
}
pacman::PressButton::PressButton(dae::GameObject* gameObject) :
	GameObjectCommand(gameObject)
{
}

void pacman::PressButton::Execute()
{
	GetGameObject()->GetComponent<pacman::ButtonComponent>()->ButtonPressed();
}

// CHEAT COMMANDS
//********
void pacman::NextLevel::Execute()
{
	dae::Event event{ "NEXT_LEVEL" };
	m_eventQueue.Invoke(std::move(event));
}

void pacman::ToggleSound::Execute()
{
	m_isOn = !m_isOn;
	if (m_isOn)
	{
#ifdef _DEBUG
		dae::ServiceLocator::RegisterSoundsystem(std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
#else
		dae::ServiceLocator::RegisterSoundsystem(std::make_unique<dae::SDLSoundSystem>());
#endif
		m_soundManager.RegisterSound();
	}
	else
	{
		dae::ServiceLocator::RegisterSoundsystem(std::make_unique<dae::NullSoundSystem>());
	}
}
