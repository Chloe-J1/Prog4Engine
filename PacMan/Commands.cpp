#include "Commands.h"
#include "../Minigin/EventQueue.h"
#include <memory>
#include "MenuManager.h"
#include "ButtonComponent.h"
#include "Events.h"
// MOVE
//********
void pacman::Move::Execute()
{
	m_moveComp->Move(m_direction);

	dae::Event directionChangedEvent{ "DIRECTION_CHANGED" };
	directionChangedEvent.arg = std::make_unique<DirectionChangedArg>(m_direction);
	dae::EventQueue::GetInstance().Invoke(std::move(directionChangedEvent), GetGameObject());
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

void pacman::PressButton::Execute()
{
	GetGameObject()->GetComponent<pacman::ButtonComponent>()->ButtonPressed();
}
