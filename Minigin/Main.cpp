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
	auto tc = new dae::TextComponent("Programming 4 Assignment", font);
	tc->SetColor({ 255, 255, 0, 255 });
	go = std::make_unique<dae::GameObject>();
	go->SetPosition(292, 20);
	go->AddComponent(tc);
	scene.Add(std::move(go));
	//// FPS
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto textGO = std::make_unique<dae::TextObject>("FPS: 0", font);
	//textGO->SetColor({ 255, 255, 0, 255 });
	//textGO->SetPosition(10, 10);

	//auto fpsGO = std::make_unique<dae::GameObject>();
	//fpsGO->SetPosition(10, 10);
	//auto fpsComp = new dae::FPSComponent();
	//fpsComp->SetTextObject(textGO.get()); // Bind textobject to fps object
	//fpsGO->AddComponent(fpsComp);

	//scene.Add(std::move(fpsGO));
	//scene.Add(std::move(textGO));
	
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	tc = new dae::TextComponent("FPS: 0", font);
	tc->SetColor({ 255, 255, 0, 255 });

	auto fpsc = new dae::FPSComponent();

	go = std::make_unique<dae::GameObject>();
	go->SetPosition(10, 10);
	go->AddComponent(fpsc);
	go->AddComponent(tc);
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
