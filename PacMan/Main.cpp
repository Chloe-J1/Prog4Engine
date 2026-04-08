#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "Commands.h"
#include "InputManager.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "HealthComponentUI.h"
#include "Subject.h"
#include "ScoreComponent.h"
#include "ScoreComponentUI.h"
#include "Hitbox.h"

#include <filesystem>
#include <glm/glm.hpp>
namespace fs = std::filesystem;



static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	// FPS
	std::unique_ptr<dae::GameObject> fpsgo = std::make_unique<dae::GameObject>();
	fpsgo->SetLocalPosition(20, 20);
	fpsgo->AddComponent<dae::RenderComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	fpsgo->AddComponent<dae::TextComponent>("FPS: ",  font);
	fpsgo->AddComponent<dae::FPSComponent>();

	scene.Add(std::move(fpsgo));


	const float speed{ 100.f };

	// Score UI -> MRS PACMAN
	std::unique_ptr<dae::GameObject> scoreGo = std::make_unique<dae::GameObject>();
	scoreGo->AddComponent<dae::RenderComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	scoreGo->AddComponent<dae::TextComponent>("Score: 0", font);
	scoreGo->AddComponent<dae::ScoreComponentUI>();

	scoreGo->SetLocalPosition(800, 10);
	// MrsPacman -> NO HEALTH COMP
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("MrsPacman.png");
	go->AddComponent<dae::SpriteComponent>(3, 1, 0.2f);
	go->AddComponent<dae::Hitbox>(16, 16);
	go->AddComponent<dae::ScoreComponent>();
	// add observer
	go->GetComponent<dae::ScoreComponent>()->GetSubject()->AddObserver(
		scoreGo->GetComponent<dae::ScoreComponentUI>()
	);

	go->SetLocalPosition(200, 200);

	dae::InputManager::GetInstance().InitializeControllers(2);

	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Right, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(1,0), speed), 0); // right
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Left, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(-1, 0), speed), 0); // left
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, -1), speed), 0); // up
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, 1), speed), 0); // down

	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_D, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(1, 0), speed)); // right
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_A, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(-1, 0), speed)); // left
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_W, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, -1), speed)); // up
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_S, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, 1), speed)); // down


	scene.Add(std::move(go));

	// Health UI
	std::unique_ptr<dae::GameObject> healthUIGo = std::make_unique<dae::GameObject>();
	healthUIGo->AddComponent<dae::RenderComponent>("Health.png");
	healthUIGo->AddComponent<dae::SpriteComponent>(1, 4, 0.f);
	healthUIGo->AddComponent<dae::HealthComponentUI>();


	healthUIGo->SetLocalPosition(480, 555);

	std::unique_ptr<dae::GameObject> goText = std::make_unique<dae::GameObject>();
	goText->SetParent(healthUIGo.get(), false);

	goText->AddComponent<dae::RenderComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
	goText->AddComponent<dae::TextComponent>("Health:", font);

	goText->SetLocalPosition(-55.f, -3);
	scene.Add(std::move(goText));

	

	

	// Pacman
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("Pacman.png");
	go->AddComponent<dae::SpriteComponent>(3, 1, 0.2f);
	go->AddComponent<dae::Hitbox>(16, 16);
	go->AddComponent<dae::HealthComponent>();
		// add observer
	go->GetComponent<dae::HealthComponent>()->GetTakeDamageEvent()->AddObserver(
		healthUIGo->GetComponent<dae::HealthComponentUI>()
	);
	go->AddComponent<dae::ScoreComponent>();
		


	go->SetLocalPosition(100, 100);


	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Right, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(1, 0), speed), 1); // right
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Left, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(-1, 0), speed), 1); // left
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, -1), speed), 1); // up
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, 1), speed), 1); // down

	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, 1), speed), 1); // down

	// trigger events
	dae::InputManager::GetInstance().BindCommand(dae::Input::Button_A, dae::TriggerEvent::PressedThisFrame, std::make_unique<dae::Damage>(go.get()), 0);
	dae::InputManager::GetInstance().BindCommand(dae::Input::Button_A, dae::TriggerEvent::PressedThisFrame, std::make_unique<dae::Damage>(go.get()), 1);

	scene.Add(std::move(healthUIGo));
	scene.Add(std::move(scoreGo));
	scene.Add(std::move(go));

	// Explanation
	std::unique_ptr<dae::GameObject> expl = std::make_unique<dae::GameObject>();
	expl->AddComponent<dae::RenderComponent>();
	expl->AddComponent<dae::TextComponent>("Use D-pad to move players     Use A to lose lives     Use B to gain points", font);
	scene.Add(std::move(expl));


	// Pellet
	std::unique_ptr<dae::GameObject> pellet = std::make_unique<dae::GameObject>();
	pellet->AddComponent<dae::Hitbox>(4, 4);
	pellet->AddComponent<dae::RenderComponent>("Pellet_small.png");
	pellet->AddComponent<dae::SmallPellet>();
	pellet->SetLocalPosition(500, 202);

	scene.Add(std::move(pellet));

	std::unique_ptr<dae::GameObject> bigpellet = std::make_unique<dae::GameObject>();
	bigpellet->AddComponent<dae::Hitbox>(8, 8);
	bigpellet->AddComponent<dae::RenderComponent>("Pellet_big.png");
	bigpellet->AddComponent<dae::PowerPellet>();
	bigpellet->SetLocalPosition(500, 212);

	scene.Add(std::move(bigpellet));
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);

	

    return 0;
}
