#pragma once
#include "../Minigin/Singleton.h"
#include "../Minigin/GameObject.h"
#include "LevelLoader.h"
#include <string>
#include <glm/glm.hpp>
#include "../Minigin/Font.h"
#include "SoundManager.h"
#include "MoveStrategies.h"
#include "../Minigin/InputManager.h"

namespace pacman
{
	class ScoreComponent;
	class HealthComponent;
	class SceneLoader final : public dae::Singleton<SceneLoader>
	{
	public:
		SceneLoader();

		// Scenes
		void GameScene(const std::string& levelname);
		void SingleplayerScene();
		void CoopScene();
		void VersusScene();
		void LoseScene();
		void WinScene();
		void MenuScene();
		void NameSelectScene();
	private:
		LevelLoader m_levelLoader{};
		const int m_player1CtrlIdx{ 0 };
		const int m_player2CtrllIdx{ 1 };
		const int m_wWidth;
		const int m_wHeight;
		

		SoundManager m_soundManager{};
		dae::InputManager& m_inputManager{ dae::InputManager::GetInstance() };

		std::unique_ptr<dae::GameObject> CreatePacman(const glm::vec2& spawnPos, const std::string& spritefile, bool usesKeyboard, bool usesController, int ctrlIdx = 0);
		std::unique_ptr<dae::GameObject> CreateScoreUI(const glm::vec2& spawnPos, dae::GameObject* pacman);
		std::unique_ptr<dae::GameObject> CreateHealthUI(const glm::vec2& spawnPos, dae::GameObject* pacman);
		std::unique_ptr<dae::GameObject> CreateGhost(const glm::vec2& spawnPos, const std::string& spritefile, std::unique_ptr<MovementBase> moveStrategy);
		std::unique_ptr<dae::GameObject> CreateButton(const glm::vec2& spawnPos, const std::string& spritefile, const std::string& name);
		std::unique_ptr<dae::GameObject> CreateText(const glm::vec2& spawnPos, const std::string& text, std::shared_ptr<dae::Font> font);
	};
}