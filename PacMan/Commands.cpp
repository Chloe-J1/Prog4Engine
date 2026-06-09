#include "Commands.h"
#include "MenuManager.h"
#include "ButtonComponent.h"

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
	/*if (m_isOn)
	{
		dae::ServiceLocator::RegisterSoundsystem(nullptr);
	}
	else
	{
		dae::ServiceLocator::RegisterSoundsystem(std::make_unique<dae::SoundSystem>());
	}*/
}
