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

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

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
	auto textComp = new dae::TextComponent("Programming 4 Assignment", font);
	textComp->SetColor({ 255, 255, 0, 255 });
	go = std::make_unique<dae::GameObject>();
	go->SetPosition(292, 20);
	go->AddComponent(textComp);
	scene.Add(std::move(go));
	// FPS
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	textComp = new dae::TextComponent("FPS: 0", font);
	textComp->SetColor({ 255, 255, 0, 255 });

	auto fpsComp = new dae::FPSComponent();

	go = std::make_unique<dae::GameObject>();
	go->SetPosition(10, 10);
	go->AddComponent(fpsComp);
	go->AddComponent(textComp);

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
