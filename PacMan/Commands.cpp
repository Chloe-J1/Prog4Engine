#include "Commands.h"
#include "MenuManager.h"
#include "ButtonComponent.h"


// MOVE
//********
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

void pacman::PressButton::Execute()
{
	GetGameObject()->GetComponent<pacman::ButtonComponent>()->ButtonPressed();
}

