#include "SceneLoader.h"
#include "../Minigin/SceneManager.h"
#include "../Minigin/RenderComponent.h"
#include "../Minigin/ResourceManager.h"
#include "../Minigin/TextComponent.h"
#include "../Minigin/InputManager.h"
#include "../Minigin/WindowConfig.h"
#include "../Minigin/Hitbox.h"
#include "../Minigin/Observer.h"
#include "../Minigin/Command.h"


#include "Commands.h"
#include "PlayerMovement.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "HealthComponentUI.h"
#include "Subject.h"
#include "ScoreComponent.h"
#include "ScoreComponentUI.h"
#include "GhostComponent.h"
#include "ButtonComponent.h"
#include "FruitSpawner.h"
#include "TargetMoverComponent.h"
#include "EatenComponent.h"


#include "Graph.h"
void pacman::SceneLoader::GameScene()
{
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene();
	//dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();

	// Background
	//***********
	std::unique_ptr<dae::GameObject> bg = std::make_unique<dae::GameObject>();
	bg->AddComponent<dae::RenderComponent>("Level_one.png");
	scene.Add(std::move(bg));

	m_levelLoader.InitLevel(scene, "Data/Maps/Level_one.txt");

	// MrsPacman
	//**********
	std::unique_ptr<dae::GameObject> mrsPacman = CreatePacman(glm::vec2{ 28,28 }, "MrsPacman.png", true, true, m_player1CtrlIdx);
	//UI
	std::unique_ptr <dae::GameObject> UI = std::make_unique<dae::GameObject>();
	UI->SetLocalPosition(10, 5);
	std::unique_ptr<dae::GameObject> scoreUI = CreateScoreUI(glm::vec2{ 0, 0 }, mrsPacman->GetComponent<pacman::ScoreComponent>());
	std::unique_ptr<dae::GameObject> healthUI = CreateHealthUI(glm::vec2{ 0, 0 }, mrsPacman->GetComponent<pacman::HealthComponent>());
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
	std::unique_ptr<dae::GameObject> scoreUIpacman = CreateScoreUI(glm::vec2{ 0, 0 }, pacman->GetComponent<pacman::ScoreComponent>());
	std::unique_ptr<dae::GameObject> healthUIpacman = CreateHealthUI(glm::vec2{ 0, 0 }, pacman->GetComponent<pacman::HealthComponent>());
	scoreUIpacman->SetParent(UIpacman.get(), false);
	healthUIpacman->SetParent(UIpacman.get(), false);
	scoreUIpacman->SetLocalPosition(0, 0);
	healthUIpacman->SetLocalPosition(-100, 0);

	

	

	//// FPS
	//std::unique_ptr<dae::GameObject> fpsgo = std::make_unique<dae::GameObject>();
	//fpsgo->SetLocalPosition(20, 20);
	//fpsgo->AddComponent<dae::RenderComponent>();
	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//fpsgo->AddComponent<dae::TextComponent>("FPS: ", font);
	//fpsgo->AddComponent<pacman::FPSComponent>();

	//scene.Add(std::move(fpsgo));

	// Fruit Spawner
	//*********
	std::unique_ptr<dae::GameObject> fruitSpawnerGo = std::make_unique<dae::GameObject>();
	fruitSpawnerGo->AddComponent<pacman::FruitSpawner>(&scene);
	scene.Add(std::move(fruitSpawnerGo));

	// Ghosts
	//**********
	std::unique_ptr<dae::GameObject> ghost = CreateGhost(glm::vec2{ 24,241 }, "Ghost_red.png", mrsPacman.get(), pacman.get(), std::make_unique<ChaseMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 217,121 }, "Ghost_pink.png", mrsPacman.get(), pacman.get(), std::make_unique<CornerMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 720,121 }, "Ghost_blue.png", pacman.get(), mrsPacman.get(), std::make_unique<CornerMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 672,672 }, "Ghost_yellow.png", mrsPacman.get(), pacman.get(), std::make_unique<SueMovement>());
	scene.Add(std::move(ghost));

	scene.Add(std::move(mrsPacman));
	scene.Add(std::move(UI));
	scene.Add(std::move(scoreUI));
	scene.Add(std::move(healthUI));

	scene.Add(std::move(pacman));
	scene.Add(std::move(UIpacman));
	scene.Add(std::move(scoreUIpacman));
	scene.Add(std::move(healthUIpacman));

	// CHECK NEIGHBORS OF A POSITION
	std::unordered_map<int, std::vector<int>> graph = pacman::Graph::GetInstance().GetGraph();
	/*for (auto neighbor : graph[229])
	{
		glm::vec2 spawnPos{ Graph::GetInstance().GetWorldPos(neighbor) };
		std::unique_ptr<dae::GameObject> wall = std::make_unique<dae::GameObject>();
		wall->AddComponent<dae::RenderComponent>("Wall.png");
		wall->SetLocalPosition(spawnPos.x, spawnPos.y);
		scene.Add(std::move(wall));
	}*/

	/*glm::vec2 spawnPos{ Graph::GetInstance().GetWorldPos(155) };
	std::unique_ptr<dae::GameObject> wall = std::make_unique<dae::GameObject>();
	wall->AddComponent<dae::RenderComponent>("Wall.png");
	wall->SetLocalPosition(spawnPos.x, spawnPos.y);
	scene.Add(std::move(wall));	*/
}

void pacman::SceneLoader::LoseScene()
{
	dae::SceneManager::GetInstance().CreateScene();
	dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent<dae::TextComponent>("GAME OVER", font);
	scene.Add(std::move(go));
}

void pacman::SceneLoader::WinScene()
{
	dae::SceneManager::GetInstance().CreateScene();
	dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent<dae::TextComponent>("GAME WON + highscore", font);

	scene.Add(std::move(go));
}

void pacman::SceneLoader::MenuScene()
{
	const int wWidth{ dae::WindowConfig::GetInstance().GetWidth() };
	const int wHeight{ dae::WindowConfig::GetInstance().GetHeight() };


	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene();
	//dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();

	// Bind MenuManager commands
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_T, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>());
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_Y, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>());
	
	// Game button
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	std::unique_ptr<dae::GameObject> button = CreateButton(glm::vec2{ float(wWidth - 72 / 2) / 2.f, float(wHeight - 24 / 2) / 2.f }, "Button.png", "LoadGameScene");
	std::unique_ptr<dae::GameObject> buttonText = CreateText(glm::vec2{ 10,4 }, "Game", font);
	buttonText->SetParent(button.get(), false);

	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));

	// Test button
	button = CreateButton(glm::vec2{ float(wWidth - 72 / 2) / 2.f, float(wHeight - 24 / 2) / 2.f + 60.f}, "Button.png", "LoadLoseScene");
	buttonText = CreateText(glm::vec2{ 10,4 }, "Lose", font);
	buttonText->SetParent(button.get(), false);

	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));

	// Explanation
	scene.Add(CreateText({ 250.f,30.f }, "Press space to play", font));
	scene.Add(CreateText({ 250.f,60.f }, "Move with WASD, pickup power pellets to eat ghosts", font));
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
	//
	constexpr int playerSize{ 16 };
	go->AddComponent<dae::Hitbox>(playerSize, playerSize);
	go->AddComponent<pacman::ScoreComponent>();
	go->AddComponent<pacman::PlayerMovement>(usesKeyboard, usesController, ctrlIdx);
	go->AddComponent<pacman::HealthComponent>();
	go->SetLayer("Player");
	go->SetLocalPosition(spawnPos.x, spawnPos.y);
	return go;
}

std::unique_ptr<dae::GameObject> pacman::SceneLoader::CreateScoreUI(const glm::vec2& spawnPos, ScoreComponent* scoreComp)
{
	std::unique_ptr<dae::GameObject> scoreGo = std::make_unique<dae::GameObject>();
	scoreGo->AddComponent<dae::RenderComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	scoreGo->AddComponent<dae::TextComponent>("Score: 0", font);
	scoreGo->AddComponent<pacman::ScoreComponentUI>();

	// add observer
	scoreComp->GetSubject()->AddObserver(
		scoreGo->GetComponent<pacman::ScoreComponentUI>()
	);

	scoreGo->SetLocalPosition(spawnPos.x, spawnPos.y);
	return scoreGo;
}

std::unique_ptr<dae::GameObject> pacman::SceneLoader::CreateHealthUI(const glm::vec2& spawnPos, HealthComponent* healthComp)
{
	std::unique_ptr<dae::GameObject> healthUIGo = std::make_unique<dae::GameObject>();
	healthUIGo->AddComponent<dae::RenderComponent>("Health.png");
	// Load sprite
	constexpr int nrCols{ 1 };
	constexpr int nrRows{ 4 };
	healthUIGo->AddComponent<dae::SpriteComponent>(nrCols, nrRows);
	//
	healthUIGo->AddComponent<pacman::HealthComponentUI>();
	// add observer
	healthComp->GetTakeDamageEvent()->AddObserver(
		healthUIGo->GetComponent<pacman::HealthComponentUI>()
	);


	healthUIGo->SetLocalPosition(spawnPos.x, spawnPos.y);
	return healthUIGo;
}

std::unique_ptr<dae::GameObject> pacman::SceneLoader::CreateGhost(const glm::vec2& spawnPos, const std::string& spritefile, dae::GameObject* firstTarget, dae::GameObject* secondTarget, std::unique_ptr<MovementBase> moveStrategy)
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
	ghost->AddComponent<pacman::GhostComponent>(std::move(moveStrategy));
	ghost->AddComponent<pacman::EatenComponent>();

	GhostComponent* comp = ghost->GetComponent<pacman::GhostComponent>();
	comp->AddTarget(firstTarget);
	comp->AddTarget(secondTarget);
	
	ghost->SetLocalPosition(spawnPos.x, spawnPos.y);
	return ghost;
}

std::unique_ptr<dae::GameObject> pacman::SceneLoader::CreateButton(const glm::vec2& spawnPos, const std::string& spritefile, const std::string& name)
{
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>(spritefile);
	// Load sprite
	constexpr int nrCols{ 1 };
	constexpr int nrRows{ 2 };
	go->AddComponent<dae::SpriteComponent>(nrCols, nrRows);
	//
	go->AddComponent<ButtonComponent>(name);

	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_SPACE, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PressButton>(go.get()));

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
