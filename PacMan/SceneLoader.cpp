#include "SceneLoader.h"
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
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "HealthComponentUI.h"
#include "ScoreComponent.h"
#include "ScoreComponentUI.h"
#include "GhostComponent.h"
#include "ButtonComponent.h"
#include "FruitSpawner.h"
#include "TargetMoverComponent.h"
#include "EatenComponent.h"
#include "PacmanAnimator.h"
#include "LetterSelectComponent.h"
#include "NameSelectComponent.h"

pacman::SceneLoader::SceneLoader():
	m_wWidth{ dae::WindowConfig::GetInstance().GetWidth() },
	m_wHeight{ dae::WindowConfig::GetInstance().GetHeight() }
{
}

void pacman::SceneLoader::GameScene(const std::string& levelname)
{
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene();

	m_levelLoader.InitLevel(scene, "Data/Levels.json", levelname);
	
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

	ghost = CreateGhost(glm::vec2{ 720,121 }, "Ghost_blue.png", std::make_unique<CornerMovement>());
	scene.Add(std::move(ghost));

	ghost = CreateGhost(glm::vec2{ 672,672 }, "Ghost_yellow.png", std::make_unique<SueMovement>());
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

void pacman::SceneLoader::LoseScene()
{
	dae::SceneManager::GetInstance().CreateScene();
	dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent<dae::TextComponent>("GAME OVER", font);
	scene.Add(std::move(go));

	// Main menu button
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	std::unique_ptr<dae::GameObject> button = CreateButton(glm::vec2{ float(m_wWidth - 72 / 2) / 2.f, float(m_wHeight - 24 / 2) / 2.f }, "Button.png", "LoadMainScene");
	std::unique_ptr<dae::GameObject> buttonText = CreateText(glm::vec2{ 10,4 }, "Home", font);
	buttonText->SetParent(button.get(), false);
	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));
}

void pacman::SceneLoader::WinScene()
{
	const int wWidth{ dae::WindowConfig::GetInstance().GetWidth() };
	const int wHeight{ dae::WindowConfig::GetInstance().GetHeight() };

	dae::SceneManager::GetInstance().CreateScene();
	dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent<dae::TextComponent>("GAME WON + highscore", font);
	scene.Add(std::move(go));

	// Main menu button
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	std::unique_ptr<dae::GameObject> button = CreateButton(glm::vec2{ float(wWidth - 72 / 2) / 2.f, float(wHeight - 24 / 2) / 2.f }, "Button.png", "LoadMainScene");
	std::unique_ptr<dae::GameObject> buttonText = CreateText(glm::vec2{ 10,4 }, "Home", font);
	buttonText->SetParent(button.get(), false);

	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));
}

void pacman::SceneLoader::MenuScene()
{


	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene();

	// Bind MenuManager commands
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>(), 0);
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_UP, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>());
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_DOWN, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>());
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>(), 0);
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>(), 1);
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>(), 1);
	
	// Sinle player button
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	std::unique_ptr<dae::GameObject> button = CreateButton(glm::vec2{ float(m_wWidth - 72 / 2) / 2.f, float(m_wHeight - 24 / 2) / 2.f }, "Button.png", "LoadSingleplayerScene");
	std::unique_ptr<dae::GameObject> buttonText = CreateText(glm::vec2{ 10,4 }, "Solo", font);
	buttonText->SetParent(button.get(), false);

	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));

	// Co-op button
	button = CreateButton(glm::vec2{ float(m_wWidth - 72 / 2) / 2.f, float(m_wHeight - 24 / 2) / 2.f + 60.f}, "Button.png", "LoadCoopScene");
	buttonText = CreateText(glm::vec2{ 10,4 }, "Co-op", font);
	buttonText->SetParent(button.get(), false);

	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));

	// Versus button
	button = CreateButton(glm::vec2{ float(m_wWidth - 72 / 2) / 2.f, float(m_wHeight - 24 / 2) / 2.f + 120.f }, "Button.png", "LoadVersusScene");
	buttonText = CreateText(glm::vec2{ 10,4 }, "Versus", font);
	buttonText->SetParent(button.get(), false);

	scene.Add(std::move(button));
	scene.Add(std::move(buttonText));

	// Explanation
	scene.Add(CreateText({ 250.f,30.f }, "Press space to play, select buttons with arrow keys / dpad", font));
	scene.Add(CreateText({ 250.f,60.f }, "Move with WASD, pickup power pellets to eat ghosts", font));
}

void pacman::SceneLoader::NameSelectScene()
{
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene();

	// Bind MenuManager commands
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>(), 0);
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>(), 0);
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>(), 1);
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>(), 1);

	// TODO: in a loop
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	std::unique_ptr<dae::GameObject> button1 = CreateButton(glm::vec2{50,70}, "Button.png", "UpP1");
	std::unique_ptr<dae::GameObject> buttonText1 = CreateText(glm::vec2{ 10,4 }, "Up", font);
	buttonText1->SetParent(button1.get(), false);
	
	std::unique_ptr<dae::GameObject> button2 = CreateButton(glm::vec2{ 50,220 }, "Button.png", "DownP1");
	std::unique_ptr<dae::GameObject>buttonText2 = CreateText(glm::vec2{ 10,4 }, "Down", font);
	buttonText2->SetParent(button2.get(), false);
	
	std::unique_ptr<dae::GameObject> button3 = CreateButton(glm::vec2{ 200,70 }, "Button.png", "UpP1");
	std::unique_ptr<dae::GameObject>buttonText3 = CreateText(glm::vec2{ 10,4 }, "Up", font);
	buttonText3->SetParent(button3.get(), false);
	
	std::unique_ptr<dae::GameObject> button4 = CreateButton(glm::vec2{ 200,220 }, "Button.png", "DownP1");
	std::unique_ptr<dae::GameObject>buttonText4 = CreateText(glm::vec2{ 10,4 }, "Down", font);
	buttonText4->SetParent(button4.get(), false);
	
	std::unique_ptr<dae::GameObject> nameLetter1 = CreateText(glm::vec2{ 50,140 }, "A", font);
	nameLetter1->AddComponent<pacman::LetterSelectComponent>(button1.get(), button2.get());
	std::unique_ptr<dae::GameObject>nameLetter2 = CreateText(glm::vec2{ 200,140 }, "A", font);
	nameLetter2->AddComponent<pacman::LetterSelectComponent>(button3.get(), button4.get());

	std::unique_ptr<dae::GameObject> selectButton = CreateButton(glm::vec2{ 50,300 }, "Button.png", "SelectName");
	std::unique_ptr<dae::GameObject>buttonText = CreateText(glm::vec2{ 10,4 }, "Select", font);
	buttonText->SetParent(selectButton.get(), false);
	selectButton->AddComponent<pacman::NameSelectComponent>();
	NameSelectComponent* nameComp{ selectButton->GetComponent<NameSelectComponent>() };
	nameComp->AddLetterComp(nameLetter1->GetComponent<LetterSelectComponent>());
	nameComp->AddLetterComp(nameLetter2->GetComponent<LetterSelectComponent>());
	scene.Add(std::move(selectButton));
	scene.Add(std::move(buttonText));
	scene.Add(std::move(nameLetter1));
	scene.Add(std::move(nameLetter2));

	scene.Add(std::move(button1));
	scene.Add(std::move(buttonText1));
	scene.Add(std::move(button2));
	scene.Add(std::move(buttonText2));
	scene.Add(std::move(button3));
	scene.Add(std::move(buttonText3));
	scene.Add(std::move(button4));
	scene.Add(std::move(buttonText4));

	auto titleFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	scene.Add(std::move(CreateText(glm::vec2{ 20,20 }, "PLAYER ONE can select a name", font)));
	scene.Add(std::move(CreateText(glm::vec2{ 20,40 }, "use dpad to choose buttons and press A to interact with the button, press select to confirm name", font)));

	
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
	go->AddComponent<pacman::ScoreComponent>();
	go->AddComponent<pacman::PlayerMovement>(usesKeyboard, usesController, ctrlIdx);
	go->AddComponent<pacman::HealthComponent>();
	go->SetLayer("Player");
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
	ghost->AddComponent<pacman::EatenComponent>();
	
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
	dae::InputManager::GetInstance().BindCommand(dae::Input::Button_A, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PressButton>(go.get()), 0);
	dae::InputManager::GetInstance().BindCommand(dae::Input::Button_A, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PressButton>(go.get()), 1);

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
