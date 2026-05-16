#include "GamestateManager.h"

void pacman::GamestateManager::Init()
{
	m_gameState = std::make_unique<MainMenuState>();
	m_gameState->OnEnter();
}
