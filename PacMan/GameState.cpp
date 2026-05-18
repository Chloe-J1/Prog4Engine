#include "GameState.h"
#include "ButtonComponent.h"
#include "SceneLoader.h"
#include "GamestateManager.h"
#include <iostream>
// MAIN MENU
void pacman::MainMenuState::OnEnter()
{
	SceneLoader::GetInstance().MenuScene();
}

std::unique_ptr<pacman::GameState> pacman::MainMenuState::Notify(dae::GameObject* sender, const dae::Event& event)
{
	if (event.id == "BUTTON_PRESSED")
	{
		ButtonComponent* button{ sender->GetComponent<ButtonComponent>() };

		if (button->GetName() == "LoadGameScene")
		{
			return std::make_unique<PlayState>();
		}
		else if (button->GetName() == "LoadLoseScene")
		{
			SceneLoader::GetInstance().LoseScene();
		}
	}
	return std::unique_ptr<pacman::GameState>();
}

// PLAY
void pacman::PlayState::OnEnter()
{
	// TODO: load scene depending on GameMode
	SceneLoader::GetInstance().GameScene();
	m_totalNrPellets = GamestateManager::GetInstance().GetTotalPellets();
}

std::unique_ptr<pacman::GameState> pacman::PlayState::Notify(dae::GameObject* , const dae::Event& event)
{
	if (event.id == "PELLET_PICKUP" || event.id == "POWER_PELLET_PICKUP")
	{
		++m_nrEatenPellets;
		if(m_nrEatenPellets >= 5)
			return std::make_unique<pacman::WinState>();
	}
	else if (event.id == "GAME_OVER")
	{
		return std::make_unique<pacman::LoseState>();
	}
	return std::unique_ptr<pacman::GameState>();
}

// maybe don't split in win & lose screen and just make a general end screen that displays info based on the gamemode

// WIN
void pacman::WinState::OnEnter()
{
	SceneLoader::GetInstance().WinScene();
}

std::unique_ptr<pacman::GameState> pacman::WinState::Notify(dae::GameObject* sender, const dae::Event& event)
{
	if (event.id == "BUTTON_PRESSED")
	{
		std::cout << "Game won\n";
		ButtonComponent* button{ sender->GetComponent<ButtonComponent>() };

		if (button->GetName() == "LoadMainScene")
		{
			return std::make_unique<pacman::MainMenuState>();
		}
	}
	return std::unique_ptr<pacman::GameState>();
}

// LOSE
void pacman::LoseState::OnEnter()
{
	SceneLoader::GetInstance().LoseScene();
}
