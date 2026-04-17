#include "Commands.h"
#include "../Minigin/EventQueue.h"
#include <memory>
#include "MenuManager.h"
// MOVE
//********
void pacman::Move::Execute()
{
	m_moveComp->Move(m_direction);

	Event directionChangedEvent{ EventId::DIRECTION_CHANGED };
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

#include "GamestateManager.h"
void pacman::GameScene::Execute()
{
	GamestateManager::GetInstance().GameScene();
}

void pacman::LoseScene::Execute()
{
	GamestateManager::GetInstance().LoseScene();
}


