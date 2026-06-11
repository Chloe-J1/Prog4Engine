#include "SceneLoader.h"
#include "../Minigin/SceneManager.h"
#include "../Minigin/RenderComponent.h"
#include "../Minigin/ResourceManager.h"
#include "../Minigin/TextComponent.h"
#include "../Minigin/WindowConfig.h"
#include "../Minigin/Hitbox.h"

#include "PlayerMovement.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "HealthComponentUI.h"
#include "ScoreComponent.h"
#include "ScoreComponentUI.h"
#include "GhostComponent.h"
#include "ButtonComponent.h"
#include "FruitSpawner.h"
#include "TargetMoverComponent.h"
#include "PacmanAnimator.h"
#include "LetterSelectComponent.h"
#include "NameSelectComponent.h"
#include "RespawnComponent.h"
#include <memory>
#include <string>


pacman::SceneLoader::SceneLoader():
	m_wWidth{ dae::WindowConfig::GetInstance().GetWidth() },
	m_wHeight{ dae::WindowConfig::GetInstance().GetHeight() },
	m_levelLoader{std::make_unique<LevelLoader>()}
{
}

void pacman::SceneLoader::GameScene(const std::string& levelname)
{
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene();

	m_levelLoader->InitLevel(scene, levelname);
	m_levelLoader->JsonToBin("Data/Levels.json", levelname);
	
	// FPS
	std::unique_ptr<dae::GameObject> fpsgo = std::make_unique<dae::GameObject>();
	fpsgo->SetLocalPosition(20, 20);
	fpsgo->AddComponent<dae::RenderComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	fpsgo->AddComponent<dae::TextComponent>("FPS: ", font);
	fpsgo->AddComponent<pacman::FPSComponent>();

	scene.Add(std::move(fpsgo));

	// Fruit Spawner
	//*********
	std::unique_ptr<dae::GameObject> fruitSpawnerGo = std::make_unique<dae::GameObject>();
	fruitSpawnerGo->AddComponent<pacman::FruitSpawner>(&scene);
	scene.Add(std::move(fruitSpawnerGo));
}

void pacman::SceneLoader::SingleplayerScene()
{
	dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();

	// MrsPacman
	//**********
	std::unique_ptr<dae::GameObject> mrsPacman = CreatePacman(glm::vec2{ 28,28 }, "MrsPacman.png", true, true, m_player1CtrlIdx);
	//UI
	std::unique_ptr <dae::GameObject> UI = std::make_unique<dae::GameObject>();
	UI->SetLocalPosition(10, 5);
	std::unique_ptr<dae::GameObject> scoreUI = CreateScoreUI(glm::vec2{ 0, 0 }, mrsPacman.get());
	std::unique_ptr<dae::GameObject> healthUI = CreateHealthUI(glm::vec2{ 0, 0 }, mrsPacman.get());
	scoreUI->SetParent(UI.get(), false);
	healthUI->SetParent(UI.get(), false);
	scoreUI->SetLocalPosition(0, 0);
	healthUI->SetLocalPosition(100, 0);

	scene.Add(std::move(mrsPacman));
	scene.Add(std::move(UI));
	scene.Add(std::move(scoreUI));
	scene.Add(std::move(healthUI));

	// Ghosts
	//**********
	std::unique_ptr<dae::GameObject> ghost = CreateGhost(glm::vec2{ 24,241 }, "Ghost_red.png", std::make_unique<ChaseMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 217,121 }, "Ghost_pink.png", std::make_unique<CornerMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 696,121 }, "Ghost_blue.png", std::make_unique<CornerMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 660,696 }, "Ghost_yellow.png", std::make_unique<SueMovement>());
	scene.Add(std::move(ghost));
}

void pacman::SceneLoader::CoopScene()
{
	dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();

	// MrsPacman
	//**********
	std::unique_ptr<dae::GameObject> mrsPacman = CreatePacman(glm::vec2{ 28,28 }, "MrsPacman.png", true, true, m_player1CtrlIdx);
	//UI
	std::unique_ptr <dae::GameObject> UI = std::make_unique<dae::GameObject>();
	UI->SetLocalPosition(10, 5);
	std::unique_ptr<dae::GameObject> scoreUI = CreateScoreUI(glm::vec2{ 0, 0 }, mrsPacman.get());
	std::unique_ptr<dae::GameObject> healthUI = CreateHealthUI(glm::vec2{ 0, 0 }, mrsPacman.get());
	scoreUI->SetParent(UI.get(), false);
	healthUI->SetParent(UI.get(), false);
	scoreUI->SetLocalPosition(0, 0);
	healthUI->SetLocalPosition(100, 0);

	// Pacman
	//**********
	std::unique_ptr<dae::GameObject> pacman = CreatePacman(glm::vec2{ 700,700 }, "Pacman.png", false, true, m_player2CtrllIdx);
	//UI
	std::unique_ptr<dae::GameObject> UIpacman = std::make_unique<dae::GameObject>();
	UIpacman->SetLocalPosition(634, 5);
	std::unique_ptr<dae::GameObject> scoreUIpacman = CreateScoreUI(glm::vec2{ 0, 0 }, pacman.get());
	std::unique_ptr<dae::GameObject> healthUIpacman = CreateHealthUI(glm::vec2{ 0, 0 }, pacman.get());
	scoreUIpacman->SetParent(UIpacman.get(), false);
	healthUIpacman->SetParent(UIpacman.get(), false);
	scoreUIpacman->SetLocalPosition(0, 0);
	healthUIpacman->SetLocalPosition(-100, 0);

	scene.Add(std::move(mrsPacman));
	scene.Add(std::move(UI));
	scene.Add(std::move(scoreUI));
	scene.Add(std::move(healthUI));

	scene.Add(std::move(pacman));
	scene.Add(std::move(UIpacman));
	scene.Add(std::move(scoreUIpacman));
	scene.Add(std::move(healthUIpacman));


	// Ghosts
	//**********
	std::unique_ptr<dae::GameObject> ghost = CreateGhost(glm::vec2{ 24,241 }, "Ghost_red.png", std::make_unique<ChaseMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 217,121 }, "Ghost_pink.png", std::make_unique<CornerMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 720,121 }, "Ghost_blue.png", std::make_unique<CornerMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 672,672 }, "Ghost_yellow.png", std::make_unique<SueMovement>());
	scene.Add(std::move(ghost));
}

void pacman::SceneLoader::VersusScene()
{
	dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();

	// MrsPacman
	//**********
	std::unique_ptr<dae::GameObject> mrsPacman = CreatePacman(glm::vec2{ 28,28 }, "MrsPacman.png", true, true, m_player1CtrlIdx);
	//UI
	std::unique_ptr <dae::GameObject> UI = std::make_unique<dae::GameObject>();
	UI->SetLocalPosition(10, 5);
	std::unique_ptr<dae::GameObject> scoreUI = CreateScoreUI(glm::vec2{ 0, 0 }, mrsPacman.get());
	std::unique_ptr<dae::GameObject> healthUI = CreateHealthUI(glm::vec2{ 0, 0 }, mrsPacman.get());
	scoreUI->SetParent(UI.get(), false);
	healthUI->SetParent(UI.get(), false);
	scoreUI->SetLocalPosition(0, 0);
	healthUI->SetLocalPosition(100, 0);

	scene.Add(std::move(mrsPacman));
	scene.Add(std::move(UI));
	scene.Add(std::move(scoreUI));
	scene.Add(std::move(healthUI));

	// Ghosts
	//**********
	std::unique_ptr<dae::GameObject> ghost = CreateGhost(glm::vec2{ 24,241 }, "Ghost_red.png", std::make_unique<NonAIMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 217,121 }, "Ghost_pink.png", std::make_unique<CornerMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 720,121 }, "Ghost_blue.png", std::make_unique<CornerMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 672,672 }, "Ghost_yellow.png", std::make_unique<SueMovement>());
	scene.Add(std::move(ghost));
}

void pacman::SceneLoader::EndScene()
{
	const int wWidth{ dae::WindowConfig::GetInstance().GetWidth() };
	const int wHeight{ dae::WindowConfig::GetInstance().GetHeight() };

	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene();

	// Highscores
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	m_scores = m_highscoreParser.GetScores("Highscores");
	glm::vec2 drawPos{ 50.f,50.f };
	const float offset{ 80.f };
	for (const auto& text : m_scores)
	{
		scene.Add(CreateText(drawPos, text, font));
		drawPos.y += offset;
	}
	// Scores
	m_scores.clear();
	m_scores = m_highscoreParser.GetScores("CurrentPlayers");
	
	drawPos = glm::vec2{ 50.f, 300.f };
	for (const auto& text : m_scores)
	{
		scene.Add(CreateText(drawPos, text, font));
		drawPos.y += offset;
	}

	// Main menu button
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	std::unique_ptr<dae::GameObject> button = CreateButton(glm::vec2{ float(wWidth - 72 / 2) / 2.f, float(wHeight - 24 / 2) / 2.f }, "Button.png");
	std::unique_ptr<dae::GameObject> buttonText = CreateText(glm::vec2{ 10,4 }, "Home", font);
	m_gamestateManager.SetHomeButton(button.get());
	buttonText->SetParent(button.get(), false);

	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));
}

void pacman::SceneLoader::MenuScene()
{
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene();

	// Sinle player button
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	std::unique_ptr<dae::GameObject> button = CreateButton(glm::vec2{ float(m_wWidth - 72 / 2) / 2.f, float(m_wHeight - 24 / 2) / 2.f }, "Button.png");
	std::unique_ptr<dae::GameObject> buttonText = CreateText(glm::vec2{ 10,4 }, "Solo", font);
	buttonText->SetParent(button.get(), false);
	m_gamestateManager.SetSoloButton(button.get());
	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));

	// Co-op button
	button = CreateButton(glm::vec2{ float(m_wWidth - 72 / 2) / 2.f, float(m_wHeight - 24 / 2) / 2.f + 60.f}, "Button.png");
	buttonText = CreateText(glm::vec2{ 10,4 }, "Co-op", font);
	buttonText->SetParent(button.get(), false);
	m_gamestateManager.SetCoopButton(button.get());
	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));

	// Versus button
	button = CreateButton(glm::vec2{ float(m_wWidth - 72 / 2) / 2.f, float(m_wHeight - 24 / 2) / 2.f + 120.f }, "Button.png");
	buttonText = CreateText(glm::vec2{ 10,4 }, "Versus", font);
	buttonText->SetParent(button.get(), false);
	m_gamestateManager.SetVersusButton(button.get());
	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));

	// Explanation
	scene.Add(CreateText({ 250.f,30.f }, "Press space to play, select buttons with arrow keys / dpad", font));
	scene.Add(CreateText({ 250.f,60.f }, "Move with WASD, pickup power pellets to eat ghosts", font));
}

void pacman::SceneLoader::NameSelectScene()
{
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	const float startY = 70.f;
	const float height = 70.f;

	for (int index = 0; index < (int)m_letterComponents.size(); ++index)
	{
		float y = startY + index * height;

		auto btnDown = CreateButton(glm::vec2{ 50.f, y }, "Button.png");
		auto btnDownText = CreateText(glm::vec2{ 10.f, 4.f }, "Down", font);
		btnDownText->SetParent(btnDown.get(), false);

		auto btnUp = CreateButton(glm::vec2{ 200.f, y }, "Button.png");
		auto btnUpText = CreateText(glm::vec2{ 10.f, 4.f }, "Up", font);
		btnUpText->SetParent(btnUp.get(), false);

		auto nameLetter = CreateText(glm::vec2{ 140.f, y }, "A", font);
		nameLetter->AddComponent<pacman::LetterSelectComponent>(btnUp.get(), btnDown.get());
		m_letterComponents[index] = nameLetter->GetComponent<LetterSelectComponent>();

		scene.Add(std::move(btnDown));
		scene.Add(std::move(btnDownText));
		scene.Add(std::move(btnUp));
		scene.Add(std::move(btnUpText));
		scene.Add(std::move(nameLetter));
	}

	auto selectButton = CreateButton(glm::vec2{ 50.f, 300.f }, "Button.png");
	auto selectText = CreateText(glm::vec2{ 10.f, 4.f }, "Select", font);
	selectText->SetParent(selectButton.get(), false);
	selectButton->AddComponent<pacman::NameSelectComponent>(selectButton.get());

	auto* nameComp = selectButton->GetComponent<NameSelectComponent>();
	for (auto* letterComp : m_letterComponents)
		nameComp->AddLetterComp(letterComp);

	scene.Add(std::move(selectButton));
	scene.Add(std::move(selectText));

	auto titleFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	scene.Add(CreateText(glm::vec2{ 20,20 }, "SELECT A NAME", font));
	scene.Add(CreateText(glm::vec2{ 20,40 }, "use dpad to choose buttons and press A to interact with the button, press select to confirm name", font));
}

// Helper functions
//******************
std::unique_ptr<dae::GameObject> pacman::SceneLoader::CreatePacman(const glm::vec2& spawnPos, const std::string& spritefile, bool usesKeyboard, bool usesController, int ctrlIdx)
{
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>(spritefile);
	// Load sprite
	int nrCols{ 3 };
	int nrRows{ 4 };
	float frameSec{ 0.2f };
	go->AddComponent<dae::SpriteComponent>(nrCols, nrRows, frameSec);
	go->AddComponent<pacman::PacmanAnimator>();
	//
	constexpr int playerSize{ 16 };
	go->AddComponent<dae::Hitbox>(playerSize, playerSize);
	go->AddComponent<pacman::ScoreComponent>(ctrlIdx);
	go->AddComponent<pacman::PlayerMovement>(usesKeyboard, usesController, ctrlIdx);
	go->AddComponent<pacman::HealthComponent>();
	go->AddComponent<pacman::RespawnComponent>(spawnPos);
	go->SetLocalPosition(spawnPos.x, spawnPos.y);
	return go;
}

std::unique_ptr<dae::GameObject> pacman::SceneLoader::CreateScoreUI(const glm::vec2& spawnPos, dae::GameObject* pacman)
{
	std::unique_ptr<dae::GameObject> scoreGo = std::make_unique<dae::GameObject>();
	scoreGo->AddComponent<dae::RenderComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	scoreGo->AddComponent<dae::TextComponent>("Score: 0", font);
	scoreGo->AddComponent<pacman::ScoreComponentUI>(pacman);

	scoreGo->SetLocalPosition(spawnPos.x, spawnPos.y);
	return scoreGo;
}

std::unique_ptr<dae::GameObject> pacman::SceneLoader::CreateHealthUI(const glm::vec2& spawnPos, dae::GameObject* pacman)
{
	std::unique_ptr<dae::GameObject> healthUIGo = std::make_unique<dae::GameObject>();
	healthUIGo->AddComponent<dae::RenderComponent>("Health.png");
	// Load sprite
	constexpr int nrCols{ 1 };
	constexpr int nrRows{ 4 };
	healthUIGo->AddComponent<dae::SpriteComponent>(nrCols, nrRows);
	//
	healthUIGo->AddComponent<pacman::HealthComponentUI>(pacman);
	


	healthUIGo->SetLocalPosition(spawnPos.x, spawnPos.y);
	return healthUIGo;
}

std::unique_ptr<dae::GameObject> pacman::SceneLoader::CreateGhost(const glm::vec2& spawnPos, const std::string& spritefile, std::unique_ptr<MovementBase> moveStrategy)
{
	std::unique_ptr<dae::GameObject> ghost = std::make_unique<dae::GameObject>();
	constexpr int ghostSize{ 24 };
	ghost->AddComponent<dae::Hitbox>(ghostSize, ghostSize);
	ghost->AddComponent<dae::RenderComponent>(spritefile);
	// Load sprite
	const int nrCols{ 2 };
	const int nrRows{ 7 };
	const float frameSec{ 0.5f };
	ghost->AddComponent<dae::SpriteComponent>(nrCols, nrRows, frameSec);
	//
	ghost->AddComponent<pacman::TargetMoverComponent>();
	if (dynamic_cast<NonAIMovement*>(moveStrategy.get())) // Ghost is controllable by a player
	{
		ghost->AddComponent<pacman::PlayerMovement>(false, true, 1);
	}
	ghost->AddComponent<pacman::GhostComponent>(std::move(moveStrategy));
	/*ghost->AddComponent<pacman::EatenComponent>();*/
	
	ghost->SetLocalPosition(spawnPos.x, spawnPos.y);
	return ghost;
}

std::unique_ptr<dae::GameObject> pacman::SceneLoader::CreateButton(const glm::vec2& spawnPos, const std::string& spritefile)
{
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>(spritefile);
	// Load sprite
	constexpr int nrCols{ 1 };
	constexpr int nrRows{ 2 };
	go->AddComponent<dae::SpriteComponent>(nrCols, nrRows);
	//
	go->AddComponent<ButtonComponent>();

	go->SetLocalPosition(spawnPos.x, spawnPos.y);

	return go;
}

std::unique_ptr<dae::GameObject> pacman::SceneLoader::CreateText(const glm::vec2& spawnPos, const std::string& text, std::shared_ptr<dae::Font> font)
{
	std::unique_ptr<dae::GameObject> textGo = std::make_unique<dae::GameObject>();
	textGo->AddComponent<dae::RenderComponent>();
	textGo->AddComponent<dae::TextComponent>(text, font);
	textGo->SetLocalPosition(spawnPos.x, spawnPos.y);

	return textGo;
}
