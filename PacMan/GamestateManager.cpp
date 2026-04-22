#include "GamestateManager.h"
#include "../Minigin/SceneManager.h"
#include "../Minigin/RenderComponent.h"
#include "../Minigin/ResourceManager.h"
#include "../Minigin/TextComponent.h"
#include "../Minigin/InputManager.h"
#include "../Minigin/WindowConfig.h"
#include "../Minigin/Hitbox.h"


#include "Commands.h"
#include "PlayerMovement.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "Commands.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "HealthComponentUI.h"
#include "Subject.h"
#include "ScoreComponent.h"
#include "ScoreComponentUI.h"
#include "Hitbox.h"
#include "Ghost.h"
#include "PlayerAnimator.h"
#include "ButtonComponent.h"
#include "Events.h"

void pacman::GamestateManager::Notify(dae::GameObject*, const dae::Event&)
{
	/*if (event.id == "PLAYER_DIED")
	{
		LoseScene();
	}*/
}

void pacman::GamestateManager::GameScene()
{
	dae::SceneManager::GetInstance().CreateScene();
	dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();

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
	UI->SetLocalPosition(10, 724);
	std::unique_ptr<dae::GameObject> scoreUI = CreateScoreUI(glm::vec2{ 0, 0 }, mrsPacman->GetComponent<pacman::ScoreComponent>());
	std::unique_ptr<dae::GameObject> healthUI = CreateHealthUI(glm::vec2{ 0, 0 }, mrsPacman->GetComponent<pacman::HealthComponent>());
	scoreUI->SetParent(UI.get(), false);
	healthUI->SetParent(UI.get(), false);
	scoreUI->SetLocalPosition(0, 0);
	healthUI->SetLocalPosition(100, 0);

	scene.Add(std::move(mrsPacman));
	scene.Add(std::move(UI));
	scene.Add(std::move(scoreUI));
	scene.Add(std::move(healthUI));

	// Pacman
	//**********
	std::unique_ptr<dae::GameObject> pacman = CreatePacman(glm::vec2{ 700,700 }, "Pacman.png", false, true, m_player2CtrllIdx);
	//UI
	UI = std::make_unique<dae::GameObject>();
	UI->SetLocalPosition(634, 724);
	scoreUI = CreateScoreUI(glm::vec2{ 0, 0 }, pacman->GetComponent<pacman::ScoreComponent>());
	healthUI = CreateHealthUI(glm::vec2{ 0, 0 }, pacman->GetComponent<pacman::HealthComponent>());
	scoreUI->SetParent(UI.get(), false);
	healthUI->SetParent(UI.get(), false);
	scoreUI->SetLocalPosition(0, 0);
	healthUI->SetLocalPosition(-100, 0);

	scene.Add(std::move(pacman));
	scene.Add(std::move(UI));
	scene.Add(std::move(scoreUI));
	scene.Add(std::move(healthUI));

	// Ghosts
	//**********
	scene.Add(CreateGhost(glm::vec2{28,256}, "Ghost_red.png"));

	// FPS
	std::unique_ptr<dae::GameObject> fpsgo = std::make_unique<dae::GameObject>();
	fpsgo->SetLocalPosition(20, 20);
	fpsgo->AddComponent<dae::RenderComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	fpsgo->AddComponent<dae::TextComponent>("FPS: ", font);
	fpsgo->AddComponent<pacman::FPSComponent>();

	scene.Add(std::move(fpsgo));
}

void pacman::GamestateManager::LoseScene()
{
	dae::SceneManager::GetInstance().CreateScene();
	dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent<dae::TextComponent>("GAME OVER", font);

	scene.Add(std::move(go));
}

void pacman::GamestateManager::MenuScene()
{
	const int wWidth{ dae::WindowConfig::GetInstance().GetWidth() };
	const int wHeight{ dae::WindowConfig::GetInstance().GetHeight() };


	dae::SceneManager::GetInstance().CreateScene();
	dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();

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
}

// Helper functions
//******************
std::unique_ptr<dae::GameObject> pacman::GamestateManager::CreatePacman(const glm::vec2& spawnPos, const std::string& spritefile, bool usesKeyboard, bool usesController, int ctrlIdx)
{
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>(spritefile);
	// Load sprite
	int nrCols{ 3 };
	int nrRows{ 4 };
	float frameSec{ 0.2f };
	go->AddComponent<dae::SpriteComponent>(nrCols, nrRows, frameSec);
	//
	go->AddComponent<pacman::PlayerAnimator>(go->GetComponent<dae::SpriteComponent>());
	constexpr int playerSize{ 16 };
	go->AddComponent<dae::Hitbox>(playerSize, playerSize);
	go->AddComponent<pacman::ScoreComponent>();
	go->AddComponent<pacman::PlayerMovement>(usesKeyboard, usesController, ctrlIdx);
	go->AddComponent<pacman::HealthComponent>();
	go->SetLocalPosition(spawnPos.x, spawnPos.y);
	return go;
}

std::unique_ptr<dae::GameObject> pacman::GamestateManager::CreateScoreUI(const glm::vec2& spawnPos, ScoreComponent* scoreComp)
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

std::unique_ptr<dae::GameObject> pacman::GamestateManager::CreateHealthUI(const glm::vec2& spawnPos, HealthComponent* healthComp)
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
	healthComp->GetTakeDamageEvent()->AddObserver(
		&pacman::GamestateManager::GetInstance()
	);

	healthUIGo->SetLocalPosition(spawnPos.x, spawnPos.y);
	return healthUIGo;
}

std::unique_ptr<dae::GameObject> pacman::GamestateManager::CreateGhost(const glm::vec2& spawnPos, const std::string& spritefile)
{
	std::unique_ptr<dae::GameObject> ghost = std::make_unique<dae::GameObject>();
	constexpr int ghostSize{ 16 };
	ghost->AddComponent<dae::Hitbox>(ghostSize, ghostSize);
	ghost->AddComponent<dae::RenderComponent>(spritefile);
	// Load sprite
	constexpr int nrCols{ 1 };
	constexpr int nrRows{ 6 };
	ghost->AddComponent<dae::SpriteComponent>(nrCols, nrRows);
	//
	ghost->AddComponent<pacman::GhostComponent>();

	ghost->SetLocalPosition(spawnPos.x, spawnPos.y);
	return ghost;
}

std::unique_ptr<dae::GameObject> pacman::GamestateManager::CreateButton(const glm::vec2& spawnPos, const std::string& spritefile, const std::string& name)
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

std::unique_ptr<dae::GameObject> pacman::GamestateManager::CreateText(const glm::vec2& spawnPos, const std::string& text, std::shared_ptr<dae::Font> font)
{
	std::unique_ptr<dae::GameObject> textGo = std::make_unique<dae::GameObject>();
	textGo->AddComponent<dae::RenderComponent>();
	textGo->AddComponent<dae::TextComponent>(text, font);
	textGo->SetLocalPosition(spawnPos.x, spawnPos.y);

	return textGo;
}
