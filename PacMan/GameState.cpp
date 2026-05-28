#include "GameState.h"
#include "ButtonComponent.h"
#include "SceneLoader.h"
#include "GamestateManager.h"
#include "MenuManager.h"

void pacman::GameState::OnEnter()
{
}

void pacman::GameState::OnExit()
{
}

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

// PLAYSTATE
void pacman::PlayState::OnEnter()
{
	SceneLoader::GetInstance().GameScene(m_levels[m_levelIdx]);
	LoadScene();

	m_totalNrPellets = GamestateManager::GetInstance().GetTotalPellets();
}

std::unique_ptr<pacman::GameState> pacman::PlayState::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "PELLET_PICKUP" || event.id == "POWER_PELLET_PICKUP")
	{
		++m_nrEatenPellets;
		if (m_nrEatenPellets >= m_totalNrPellets)
		{
			++m_levelIdx;
			if (m_levelIdx >= 3)
			{
				return std::make_unique<pacman::WinState>();
			}
			else
			{
				SceneLoader::GetInstance().GameScene(m_levels[m_levelIdx]);
				LoadScene();
			}
			m_nrEatenPellets = 0;
		}
	}
	else if (event.id == "PLAYER_DIED")
	{
		++m_nrDeaths;
		if (m_nrDeaths >= m_nrPacman)
			return std::make_unique<pacman::LoseState>();
	}

	return nullptr;
}

// SINGLEPLAYER
void pacman::SingleplayerState::LoadScene()
{
	SceneLoader::GetInstance().SingleplayerScene();
}

//COOP 
void pacman::CoopState::LoadScene()
{
	SceneLoader::GetInstance().CoopScene();
}

// VERSUS
void pacman::VersusState::LoadScene()
{
	SceneLoader::GetInstance().VersusScene();
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

// NAME SELECT
void pacman::NameSelectState::OnEnter()
{
	m_inputManager.DisableController(1);
}

std::unique_ptr<pacman::GameState> pacman::NameSelectState::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "NAME_SELECTED")
	{
		m_nrSelectedNames++;
		if (m_nrSelectedNames >= m_maxNrPlayers)
		{
			return std::make_unique<pacman::MainMenuState>();
		}
		else if (m_nrSelectedNames == 1)
		{
			m_inputManager.EnableController(1);
			m_inputManager.DisableController(0);
		}
	}
	return nullptr;
}

void pacman::NameSelectState::OnExit()
{
	m_inputManager.EnableAllControllers();
	MenuManager::GetInstance().ResetSelected();
}
