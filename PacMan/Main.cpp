
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "../Minigin/InputManager.h"
#include "GamestateManager.h"
#include "SceneLoader.h"
#include <nlohmann/json.hpp>
#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;

static void ClearCurrentPlayers()
{
	std::filesystem::path filePath = std::filesystem::path(DATA_PATH) / "Scores.json";

	nlohmann::json data;
	std::ifstream iFile(filePath);
	data = nlohmann::json::parse(iFile);
	iFile.close();

	data["CurrentPlayers"] = nlohmann::json::array();

	std::ofstream oFile(filePath);
	oFile << data.dump(4);
}

static void load()
{
	const int nrControllers{ 2 };
	dae::InputManager::GetInstance().InitializeControllers(nrControllers);
	pacman::GamestateManager::GetInstance().Init();
	ClearCurrentPlayers();
	pacman::SceneLoader::GetInstance().NameSelectScene();
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
