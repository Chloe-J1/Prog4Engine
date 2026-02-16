#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "RenderComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	//// Background
	//auto go = std::make_unique<dae::GameObject>();
	//go->SetTexture("background.png");
	//scene.Add(std::move(go));
	//// Logo
	//go = std::make_unique<dae::GameObject>();
	//go->SetTexture("logo.png");
	//go->SetPosition(358, 180);
	//scene.Add(std::move(go));
	//// Title
	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_unique<dae::TextObject>("Programming 4 Assignment", font);
	//to->SetColor({ 255, 255, 0, 255 });
	//to->SetPosition(292, 20);
	//scene.Add(std::move(to));
	//// FPS
	//go = std::make_unique<dae::GameObject>();
	//go->SetTexture("logo.png");
	//go->SetPosition(10, 10);
	//scene.Add(std::move(go));

	// Background
	auto go = std::make_unique<dae::GameObject>();
	dae::RenderComponent* renderComp = new dae::RenderComponent();
	renderComp->SetTexture("background.png");
	go->AddComponent(renderComp);
	scene.Add(std::move(go));
	// Logo
	go = std::make_unique<dae::GameObject>();
	renderComp = new dae::RenderComponent();
	renderComp->SetTexture("logo.png");
	go->AddComponent(renderComp);
	go->SetPosition(358, 180);
	scene.Add(std::move(go));
	// Title
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<dae::TextObject>("Programming 4 Assignment", font);
	to->SetColor({ 255, 255, 0, 255 });
	to->SetPosition(292, 20);
	scene.Add(std::move(to));
	// FPS
	go = std::make_unique<dae::GameObject>();
	renderComp = new dae::RenderComponent();
	renderComp->SetTexture("logo.png");
	go->AddComponent(renderComp);
	go->SetPosition(10, 10);
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
