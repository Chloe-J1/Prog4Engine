#pragma once
#include "../Minigin/Singleton.h"
#include "../Minigin/GameObject.h"
#include <string>
#include <glm/glm.hpp>
#include "../Minigin/Font.h"
#include "MoveStrategies.h"
#include "../Minigin/InputManager.h"
#include <memory>
#include "LevelLoader.h"
#include "HighscoreParser.h"
#include <vector>
#include <array>
#include "GamestateManager.h"
 
namespace pacman
{
	class ScoreComponent;
	class HealthComponent;
	class LetterSelectComponent;
	class SceneLoader final : public dae::Singleton<SceneLoader>
	{
	public:
		explicit SceneLoader();

		// Scenes
		void GameScene(const std::string& levelname);
		void SingleplayerScene();
		void CoopScene();
		void VersusScene();
		void EndScene();
		void MenuScene();
		void NameSelectScene();
	private:
		const int m_wWidth;
		const int m_wHeight;
		std::unique_ptr<LevelLoader> m_levelLoader;
		std::unique_ptr<HighscoreParser> m_highscoreParser;
		std::vector<std::string> m_scores{};

		const int m_player1CtrlIdx{ 0 };
		const int m_player2CtrllIdx{ 1 };
		
		dae::InputManager& m_inputManager{ dae::InputManager::GetInstance() };
		GamestateManager& m_gamestateManager{ pacman::GamestateManager::GetInstance() };
		std::array<LetterSelectComponent*, 3> m_letterComponents{};

		std::unique_ptr<dae::GameObject> CreatePacman(const glm::vec2& spawnPos, const std::string& spritefile, bool usesKeyboard, bool usesController, int ctrlIdx = 0);
		std::unique_ptr<dae::GameObject> CreateScoreUI(const glm::vec2& spawnPos, dae::GameObject* pacman);
		std::unique_ptr<dae::GameObject> CreateHealthUI(const glm::vec2& spawnPos, dae::GameObject* pacman);
		std::unique_ptr<dae::GameObject> CreateGhost(const glm::vec2& spawnPos, const std::string& spritefile, std::unique_ptr<MovementBase> moveStrategy);
		std::unique_ptr<dae::GameObject> CreateButton(const glm::vec2& spawnPos, const std::string& spritefile);
		std::unique_ptr<dae::GameObject> CreateText(const glm::vec2& spawnPos, const std::string& text, std::shared_ptr<dae::Font> font);
	};
}