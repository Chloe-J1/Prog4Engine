#include "GameState.h"
#include "ButtonComponent.h"
#include "SceneLoader.h"

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
			return std::unique_ptr<PlayGameState>();
		}
		else if (button->GetName() == "LoadLoseScene")
		{
			SceneLoader::GetInstance().LoseScene();
		}
	}
	return std::unique_ptr<pacman::GameState>();
}

// PLAY
void pacman::PlayGameState::OnEnter()
{
	// TODO: load scene depending on GameMode
	SceneLoader::GetInstance().GameScene();
}

std::unique_ptr<pacman::GameState> pacman::PlayGameState::Notify(dae::GameObject* , const dae::Event& )
{
	// PLAYER DEATH / WIN -> transition to highscore menu
	return std::unique_ptr<pacman::GameState>();
}


