#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "GamestateManager.h"
#include "WindowConfig.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	dae::InputManager::GetInstance().InitializeControllers(2);
	//pacman::GamestateManager::GetInstance().GameScene();
	//pacman::GamestateManager::GetInstance().LoseScene();
	//pacman::GamestateManager::GetInstance().MapScene();
	pacman::GamestateManager::GetInstance().MenuScene();
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	const int wWidth{ 744 };
	const int wHeight{ 744 };
	const std::string title{ "Prog4 Exam" };
	dae::Minigin engine(data_location, wWidth, wHeight, title);
	engine.Run(load);

	

    return 0;
}
