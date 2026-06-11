#include "LevelLoader.h"
#include <fstream>
#include <string>
#include "../Minigin/RenderComponent.h"
#include "../Minigin/Hitbox.h"
#include "Pellets.h"
#include "Graph.h"
#include "GamestateManager.h"
#include <iostream>
#include <nlohmann/json.hpp>

void pacman::LevelLoader::InitLevel(dae::Scene& scene, const std::string& levelname)
{
	m_pathIndices.clear();
	
#ifdef _DEBUG
	ParseJson(scene, levelname);
#else
	ParseBin(scene, levelname);
#endif

}

std::unique_ptr<dae::GameObject> pacman::LevelLoader::CreatePellet(float x, float y)
{
	constexpr int offset{ 10 };
	constexpr int size{ 4 };
	std::unique_ptr<dae::GameObject> pellet = std::make_unique<dae::GameObject>();
	pellet->AddComponent<dae::Hitbox>(size, size);
	pellet->AddComponent<dae::RenderComponent>("Pellet_small.png");
	pellet->AddComponent<pacman::SmallPellet>();
	pellet->SetLocalPosition(x + offset, y + offset);
	return pellet;
}

std::unique_ptr<dae::GameObject> pacman::LevelLoader::CreatePowerPellet(float x, float y)
{
	constexpr int offset{ 8 };
	constexpr int size{ 8 };
	std::unique_ptr<dae::GameObject> pellet = std::make_unique<dae::GameObject>();
	pellet->AddComponent<dae::Hitbox>(size, size);
	pellet->AddComponent<dae::RenderComponent>("Pellet_big.png");
	pellet->AddComponent<pacman::PowerPellet>();
	pellet->SetLocalPosition(x + offset, y + offset);
	return pellet;
}

void pacman::LevelLoader::ParseBin(dae::Scene& scene, const std::string& levelname)
{
	// Add background
	std::unique_ptr<dae::GameObject> bg = std::make_unique<dae::GameObject>();
	bg->AddComponent<dae::RenderComponent>(levelname + ".png");
	scene.Add(std::move(bg));

	std::string filename{ "Data/" + levelname + ".bin"};
	std::ifstream iFile;
	int nrPellets{};
	iFile.open(filename, std::ios::binary | std::ios::out);
	if (iFile.is_open())
	{
		int value{};
		float x{};
		float y{};
		int pathIdx{ 0 };
		
		for (int row = 0; row < m_nrRows; ++row)
		{
			for (int col = 0; col < m_nrCols; ++col)
			{
				iFile.read(reinterpret_cast<char*>(&value), sizeof(value));

				if (value == 0)
				{
					scene.Add(CreatePellet(x, y));
					m_pathIndices.insert(pathIdx);
					++nrPellets;
				}
				else if (value == 1)
				{
					scene.Add(CreatePowerPellet(x, y));
					m_pathIndices.insert(pathIdx);
					++nrPellets;
				}
				else if (value == 2)
				{
					m_pathIndices.insert(pathIdx);
				}

				x += m_cellsize;
				++pathIdx;
				std::cout << x << "\n";
			}
			y += m_cellsize;
			x = 0;
		}
	}
	else
	{
		std::cerr << "Couldn't open file: " << filename << "\n";
	}
	iFile.close();

	// Give the graph all walkable indices
	Graph::GetInstance().SetNeighbors(m_pathIndices);
	GamestateManager::GetInstance().SetTotalPellets(nrPellets);
}

void pacman::LevelLoader::ParseJson(dae::Scene& scene, const std::string& levelname)
{
	std::string filename{ "Data/Levels.json" };
	std::ifstream iFile(filename);
	if (iFile.is_open() == false)
	{
		std::cerr << "Can't open file: " << filename << "\n";
		return;
	}
	float x{};
	float y{};

	int pathIdx{ 0 };

	int nrPellets{};

	// Add background
	std::unique_ptr<dae::GameObject> bg = std::make_unique<dae::GameObject>();
	bg->AddComponent<dae::RenderComponent>(levelname + ".png");
	scene.Add(std::move(bg));

	// Level layout

	nlohmann::json data;
	try
	{
		data = nlohmann::json::parse(iFile);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		std::cerr << "JSON parse error in " << filename << ": " << e.what() << "\n";
		return;
	}

	if (not data.contains(levelname))
	{
		std::cerr << "Level not found: " << levelname << "\n";
		return;
	}
	for (const auto& line : data[levelname])
	{
		std::string row = line;
		for (const auto& item : row)
		{
			if (item == ',') continue; // ignore
			if (item == 'p')
			{
				scene.Add(CreatePellet(x, y));
				m_pathIndices.insert(pathIdx);
				++nrPellets;
			}
			else if (item == 'P')
			{
				scene.Add(CreatePowerPellet(x, y));
				m_pathIndices.insert(pathIdx);
				++nrPellets;
			}
			else if (item == 'b')
			{
				m_pathIndices.insert(pathIdx);
			}

			x += m_cellsize;
			pathIdx++;
		}
		y += m_cellsize;
		x = 0;
	}

	iFile.close();

	// Give the graph all walkable indices
	Graph::GetInstance().SetNeighbors(m_pathIndices);
	GamestateManager::GetInstance().SetTotalPellets(nrPellets);
}

void pacman::LevelLoader::JsonToBin(const std::string& jsonFile, const std::string& levelname)
{
	std::ifstream iFile{ jsonFile };
	if (!iFile.is_open())
	{
		std::cerr << "Can't open: " << jsonFile << "\n";
		return;
	}

	nlohmann::json data;
	try 
	{
		data = nlohmann::json::parse(iFile);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		std::cerr << "Parse error: " << e.what() << "\n";
		return;
	}
	iFile.close();

	if (not data.contains(levelname)) return;
	

	std::ofstream oFile{ levelname + ".bin", std::ios::binary };
	for (const auto& line : data[levelname])
	{
		std::string row = line;
		for (const auto& item : row)
		{
			if (item == ',') continue;
			int value{};
			if (item == 'p') value = 0;
			else if (item == 'P') value = 1;
			else if (item == 'b') value = 2;
			else if (item == 'w') value = 3;

			oFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
		}
	}
	oFile.close();
}
