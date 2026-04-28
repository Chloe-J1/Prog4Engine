#pragma once
#include "../Minigin/Singleton.h"
#include "../Minigin/Observer.h"
#include "../Minigin/GameObject.h"
#include "LevelLoader.h"
#include <string>
#include <glm/glm.hpp>
#include "../Minigin/Font.h"
#include "SoundManager.h"
namespace pacman
{
	class ScoreComponent;
	class HealthComponent;
	class GamestateManager final : public dae::Singleton<GamestateManager>, public dae::Observer
	{
	public:
		GamestateManager():
			m_levelLoader{}
		{
		}

		virtual void Notify(dae::GameObject*, const dae::Event&) override;
		// Scenes
		void GameScene();
		void LoseScene();
		void MenuScene();
	private:
		LevelLoader m_levelLoader;
		const int m_player1CtrlIdx{ 0 };
		const int m_player2CtrllIdx{ 1 };

		SoundManager m_soundManager{};

		std::unique_ptr<dae::GameObject> CreatePacman(const glm::vec2& spawnPos, const std::string& spritefile, bool usesKeyboard, bool usesController, int ctrlIdx = 0);
		std::unique_ptr<dae::GameObject> CreateScoreUI(const glm::vec2& spawnPos, ScoreComponent* scoreComp);
		std::unique_ptr<dae::GameObject> CreateHealthUI(const glm::vec2& spawnPos, HealthComponent* healthComp);
		std::unique_ptr<dae::GameObject> CreateGhost(const glm::vec2& spawnPos, const std::string& spritefile);
		std::unique_ptr<dae::GameObject> CreateButton(const glm::vec2& spawnPos, const std::string& spritefile, const std::string& name);
		std::unique_ptr<dae::GameObject> CreateText(const glm::vec2& spawnPos, const std::string& text, std::shared_ptr<dae::Font> font);
	};
}