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

		if (button->GetName() == "LoadSingleplayerScene")
		{
			return std::make_unique<SingleplayerState>();
		}
		else if (button->GetName() == "LoadCoopScene")
		{
			return std::make_unique<CoopState>();
		}
		else if (button->GetName() == "LoadVersusScene")
		{
			return std::make_unique<VersusState>();
		}
	}
	return nullptr;
}

// SINGLEPLAYER
void pacman::SingleplayerState::OnEnter()
{
	SceneLoader::GetInstance().GameScene();
	SceneLoader::GetInstance().SingleplayerScene();

	m_totalNrPellets = GamestateManager::GetInstance().GetTotalPellets();
}

std::unique_ptr<pacman::GameState> pacman::SingleplayerState::Notify(dae::GameObject* , const dae::Event& event)
{
	if (event.id == "PELLET_PICKUP" || event.id == "POWER_PELLET_PICKUP")
	{
		++m_nrEatenPellets;
		if (m_nrEatenPellets >= m_totalNrPellets)
			return std::make_unique<pacman::WinState>();
	}
	else if (event.id == "PLAYER_DIED")
	{
		++m_nrDeaths;
		if (m_nrDeaths >= m_nrPacman)
			return std::make_unique<pacman::LoseState>();
	}

	return nullptr;
}


//COOP
void pacman::CoopState::OnEnter()
{
	SceneLoader::GetInstance().GameScene();
	SceneLoader::GetInstance().CoopScene();

	m_totalNrPellets = GamestateManager::GetInstance().GetTotalPellets();
}

std::unique_ptr<pacman::GameState> pacman::CoopState::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "PELLET_PICKUP" || event.id == "POWER_PELLET_PICKUP")
	{
		++m_nrEatenPellets;
		if (m_nrEatenPellets >= m_totalNrPellets)
			return std::make_unique<pacman::WinState>();
	}
	else if (event.id == "PLAYER_DIED")
	{
		++m_nrDeaths;
		if (m_nrDeaths >= m_nrPacman)
			return std::make_unique<pacman::LoseState>();
	}

	return nullptr;
}

// VERSUS
void pacman::VersusState::OnEnter()
{
	SceneLoader::GetInstance().GameScene();
	SceneLoader::GetInstance().VersusScene();

	m_totalNrPellets = GamestateManager::GetInstance().GetTotalPellets();
}

std::unique_ptr<pacman::GameState> pacman::VersusState::Notify(dae::GameObject* , const dae::Event& event)
{
	if (event.id == "PELLET_PICKUP" || event.id == "POWER_PELLET_PICKUP")
	{
		++m_nrEatenPellets;
		if (m_nrEatenPellets >= m_totalNrPellets)
			return std::make_unique<pacman::WinState>();
	}
	else if (event.id == "PLAYER_DIED")
	{
		++m_nrDeaths;
		if (m_nrDeaths >= m_nrPacman)
			return std::make_unique<pacman::LoseState>();
	}

	return nullptr;
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
		ButtonComponent* button{ sender->GetComponent<ButtonComponent>() };

		if (button->GetName() == "LoadMainScene")
		{
			return std::make_unique<pacman::MainMenuState>();
		}
	}
	return nullptr;
}

// LOSE
void pacman::LoseState::OnEnter()
{
	SceneLoader::GetInstance().LoseScene();
}

std::unique_ptr<pacman::GameState> pacman::LoseState::Notify(dae::GameObject* sender, const dae::Event& event)
{
	if (event.id == "BUTTON_PRESSED")
	{
		ButtonComponent* button{ sender->GetComponent<ButtonComponent>() };

		if (button->GetName() == "LoadMainScene")
		{
			return std::make_unique<pacman::MainMenuState>();
		}
	}
	return nullptr;
}


