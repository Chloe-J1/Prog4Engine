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
#include "RotationComponent.h"
#include "FPSComponent.h"
#include "GraphComponent.h"
#include "Commands.h"
#include "InputManager.h"

#include <filesystem>
#include <glm/glm.hpp>
namespace fs = std::filesystem;



static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	//// Pacman
	//std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	//go->SetLocalPosition( 300.f, 300.f);

	//dae::RenderComponent* renderComp = new dae::RenderComponent(go.get());
	//renderComp->SetTexture("Pacman.png");
	//go->AddComponent(renderComp);
	//dae::RotationComponent* rotComp = new dae::RotationComponent(go.get(), 2.f);
	//go->AddComponent(rotComp);
	//

	//// Mrs pacman
	//std::unique_ptr<dae::GameObject> cGo = std::make_unique<dae::GameObject>();
	//cGo->SetLocalPosition( 50.f, 50.f);
	//renderComp = new dae::RenderComponent(cGo.get());
	//renderComp->SetTexture("Female_pacman.png");
	//cGo->AddComponent(renderComp);
	//cGo->SetParent(go.get(), false);
	//rotComp = new dae::RotationComponent(cGo.get(), 20.f, false);
	//cGo->AddComponent(rotComp);

	//scene.Add(std::move(go));
	//scene.Add(std::move(cGo));

	//// FPS
	//std::unique_ptr<dae::GameObject> fpsgo = std::make_unique<dae::GameObject>();
	//fpsgo->SetLocalPosition(20, 20);
	//fpsgo->AddComponent<dae::FPSComponent>();
	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//fpsgo->AddComponent<dae::TextComponent>("FPS: ",  font);
	//fpsgo->AddComponent<dae::RenderComponent>();

	//scene.Add(std::move(go));

	//// UI
	//std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	//dae::GraphComponent* graphComp = new dae::GraphComponent(go.get());
	//go->AddComponent(graphComp);
	//scene.Add(std::move(go));
	const float speed{ 70.f };

	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("MrsPacman.png", 3, 1, 0.2f);
	
	go->SetLocalPosition(200, 200);

	dae::InputManager::GetInstance().InitializeControllers(2);

	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Right, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(1,0), speed), 0); // right
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Left, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(-1, 0), speed), 0); // left
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, -1), speed), 0); // up
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, 1), speed), 0); // down

	scene.Add(std::move(go));
	//TEMP
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("Pacman.png");


	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Right, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(1, 0), speed), 1); // right
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Left, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(-1, 0), speed), 1); // left
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Up, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, -1), speed), 1); // up
	dae::InputManager::GetInstance().BindCommand(dae::Input::DPad_Down, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, 1), speed), 1); // down

	scene.Add(std::move(go));


	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("Pacman.png");

	go->SetLocalPosition(300, 200);

	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_D, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(1, 0), speed*2)); // right
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_A, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(-1, 0), speed*2)); // left
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_W, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, -1), speed*2)); // up
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_S, dae::TriggerEvent::Hold, std::make_unique<dae::Move>(go.get(), glm::vec2(0, 1), speed*2)); // down

	scene.Add(std::move(go));
	
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
