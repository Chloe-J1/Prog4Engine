#pragma once
#include "../Minigin/Singleton.h"
#include "../Minigin/Observer.h"
#include "../Minigin/GameObject.h"
#include "LevelLoader.h"
#include <string>
#include <glm/glm.hpp>
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
		void MapScene();
		void GameScene();
		void LoseScene();
		void MenuScene();
	private:
		LevelLoader m_levelLoader;

		std::unique_ptr<dae::GameObject> CreatePacman(const std::string& spritefile, const glm::vec2& spawnPos, bool usesKeyboard, bool usesController, int ctrlIdx = 0);
		std::unique_ptr<dae::GameObject> CreateScoreUI(const glm::vec2& spawnPos, ScoreComponent* scoreComp);
		std::unique_ptr<dae::GameObject> CreateHealthUI(const glm::vec2& spawnPos, HealthComponent* healthComp);
	};
}