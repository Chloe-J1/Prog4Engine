#include "GameState.h"
#include "SceneLoader.h"
#include "GamestateManager.h"
#include "MenuManager.h"
#include "Commands.h"
#include "Events.h"
#include <iostream>

pacman::GameState::GameState()
{
	m_gamestateManager = &GamestateManager::GetInstance();
}

void pacman::GameState::OnEnter()
{
}

std::unique_ptr<pacman::GameState> pacman::GameState::Notify(const dae::Event&)
{
	return nullptr;
}

void pacman::GameState::OnExit()
{
}

// MAIN MENU
void pacman::MainMenuState::OnEnter()
{
	SceneLoader::GetInstance().MenuScene();

	// Bind MenuScene commands
	m_inputManager.BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>(), 0);
	m_inputManager.BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>(), 1);
	m_inputManager.BindCommand(SDL_SCANCODE_UP, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>());
	m_inputManager.BindCommand(SDL_SCANCODE_DOWN, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>());
	m_inputManager.BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>(), 0);
	m_inputManager.BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>(), 1);
}

std::unique_ptr<pacman::GameState> pacman::MainMenuState::Notify(const dae::Event& event)
{
	if (event.id == "BUTTON_PRESSED")
	{
		auto* arg = static_cast<SenderArg*>(event.arg.get());
		dae::GameObject* sender{ arg->sender };
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

	m_inputManager.UnbindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, 0);
	m_inputManager.UnbindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, 1);
	m_inputManager.UnbindCommand(SDL_SCANCODE_UP, dae::TriggerEvent::PressedThisFrame);
	m_inputManager.UnbindCommand(SDL_SCANCODE_DOWN, dae::TriggerEvent::PressedThisFrame);
	m_inputManager.UnbindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, 0);
	m_inputManager.UnbindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, 1);
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

	// Skip level cmd
	m_inputManager.BindCommand(SDL_SCANCODE_F1, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextLevel>());
}

std::unique_ptr<pacman::GameState> pacman::PlayState::Notify(const dae::Event& event)
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
	else if (event.id == "NEXT_LEVEL")
	{
		return NextLevel();
	}

	return nullptr;
}

void pacman::PlayState::OnExit()
{
	m_inputManager.UnbindCommand(SDL_SCANCODE_F1, dae::TriggerEvent::PressedThisFrame);
}

std::unique_ptr<pacman::GameState> pacman::PlayState::NextLevel()
{
	++m_levelIdx;
	if (m_levelIdx > 2)
	{
		return std::make_unique<pacman::EndState>();
	}
	else
	{
		SceneLoader::GetInstance().GameScene(m_levels[m_levelIdx]);
		LoadScene();
	}
	m_nrEatenPellets = 0;
	return nullptr;
}

// SINGLEPLAYER
pacman::SingleplayerState::SingleplayerState(int nrPacman):
	PlayState(nrPacman)
{
}

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

std::unique_ptr<pacman::GameState> pacman::EndState::Notify(const dae::Event& event)
{
	if (event.id == "BUTTON_PRESSED")
	{
		auto* arg = static_cast<SenderArg*>(event.arg.get());
		dae::GameObject* sender{ arg->sender };
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
	m_highscoreParser.ClearScores();
}

// NAME SELECT
void pacman::NameSelectState::OnEnter()
{
	// Bind NameSelect commands
	m_inputManager.BindCommand(dae::Input::DPad_Left, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>(), 0);
	m_inputManager.BindCommand(dae::Input::DPad_Right, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>(), 0);
	m_inputManager.BindCommand(SDL_SCANCODE_LEFT, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>());
	m_inputManager.BindCommand(SDL_SCANCODE_RIGHT, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>());
	m_inputManager.BindCommand(dae::Input::DPad_Left, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>(), 1);
	m_inputManager.BindCommand(dae::Input::DPad_Right, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>(), 1);
	
	m_inputManager.DisableController(1);
}

std::unique_ptr<pacman::GameState> pacman::NameSelectState::Notify(const dae::Event& event)
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

	m_inputManager.UnbindCommand(dae::Input::DPad_Left, dae::TriggerEvent::PressedThisFrame, 0);
	m_inputManager.UnbindCommand(dae::Input::DPad_Right, dae::TriggerEvent::PressedThisFrame, 0);
	m_inputManager.UnbindCommand(SDL_SCANCODE_LEFT, dae::TriggerEvent::PressedThisFrame);
	m_inputManager.UnbindCommand(SDL_SCANCODE_RIGHT, dae::TriggerEvent::PressedThisFrame);
	m_inputManager.UnbindCommand(dae::Input::DPad_Left, dae::TriggerEvent::PressedThisFrame, 1);
	m_inputManager.UnbindCommand(dae::Input::DPad_Right, dae::TriggerEvent::PressedThisFrame, 1);
}
