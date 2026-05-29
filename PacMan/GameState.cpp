#include "GameState.h"
#include "ButtonComponent.h"
#include "SceneLoader.h"
#include "GamestateManager.h"
#include "MenuManager.h"

pacman::GameState::GameState()
{
	m_gamestateManager = &GamestateManager::GetInstance();
}

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
		if (sender == m_gamestateManager->GetSoloButton())
		{
			return std::make_unique<SingleplayerState>(1);
		}
		else if (sender == m_gamestateManager->GetCoopButton())
		{
			return std::make_unique<CoopState>(2);
		}
		else if (sender == m_gamestateManager->GetVersusButton())
		{
			return std::make_unique<VersusState>(1);
		}
	}
	return nullptr;
}

void pacman::MainMenuState::OnExit()
{
	m_gamestateManager->ClearButtons();
}

pacman::PlayState::PlayState(int nrPacman):
	m_nrPacman{nrPacman}
{
}

// PLAYSTATE
void pacman::PlayState::OnEnter()
{
	SceneLoader::GetInstance().GameScene(m_levels[m_levelIdx]);
	LoadScene();

	m_totalNrPellets = m_gamestateManager->GetTotalPellets();
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
				return std::make_unique<pacman::EndState>();
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
			return std::make_unique<pacman::EndState>();
	}

	return nullptr;
}

pacman::SingleplayerState::SingleplayerState(int nrPacman):
	PlayState(nrPacman)
{
}

// SINGLEPLAYER
void pacman::SingleplayerState::LoadScene()
{
	SceneLoader::GetInstance().SingleplayerScene();
}

pacman::CoopState::CoopState(int nrPacman):
	PlayState(nrPacman)
{
}

//COOP 
void pacman::CoopState::LoadScene()
{
	SceneLoader::GetInstance().CoopScene();
}

pacman::VersusState::VersusState(int nrPacman):
	PlayState(nrPacman)
{
}

// VERSUS
void pacman::VersusState::LoadScene()
{
	SceneLoader::GetInstance().VersusScene();
}

// END
void pacman::EndState::OnEnter()
{
	SceneLoader::GetInstance().EndScene();
}

std::unique_ptr<pacman::GameState> pacman::EndState::Notify(dae::GameObject* sender, const dae::Event& event)
{
	if (event.id == "BUTTON_PRESSED")
	{
		if (sender == m_gamestateManager->GetHomeButton())
		{
			return std::make_unique<pacman::MainMenuState>();
		}
	}
	return nullptr;
}

void pacman::EndState::OnExit()
{
	m_gamestateManager->ClearButtons();
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
