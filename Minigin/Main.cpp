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

#include <filesystem>
#include <glm/glm.hpp>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	// Pacman
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition(glm::vec3{ 300.f, 300.f,0 });

	dae::RenderComponent* renderComp = new dae::RenderComponent(go.get());
	renderComp->SetTexture("Pacman.png");
	go->AddComponent(renderComp);
	dae::RotationComponent* rotComp = new dae::RotationComponent(go.get(), 2.f);
	go->AddComponent(rotComp);
	

	// Mrs pacman
	std::unique_ptr<dae::GameObject> cGo = std::make_unique<dae::GameObject>();
	cGo->SetLocalPosition(glm::vec3{ 50.f, 50.f,0 });
	renderComp = new dae::RenderComponent(cGo.get());
	renderComp->SetTexture("Female_pacman.png");
	cGo->AddComponent(renderComp);
	cGo->SetParent(go.get(), false);
	rotComp = new dae::RotationComponent(cGo.get(), 20.f, false);
	cGo->AddComponent(rotComp);

	scene.Add(std::move(go));
	scene.Add(std::move(cGo));

	


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
