#include "LevelLoader.h"
#include <sstream>
#include <fstream>
#include <string>
#include "../Minigin/RenderComponent.h"
#include "../Minigin/Hitbox.h"

#include "Pellets.h"
#include <unordered_set>
#include "Graph.h"
#include "GamestateManager.h"
#include <iostream>

void pacman::LevelLoader::InitLevel(dae::Scene& scene, const std::string& filename)
{
	std::ifstream iFile;
	iFile.open(filename);
	std::string line;
	float x{};
	float y{};

	std::unordered_set<int> pathIndices;
	int pathIdx{ 0 };

	int nrPellets{};

	if (iFile.is_open())
	{
		while (std::getline(iFile, line))
		{
			std::stringstream ss(line);
			std::string type;

			while (std::getline(ss, type, ','))
			{
				
				if (type == "p")
				{
					scene.Add(CreatePellet(x, y));
					pathIndices.insert(pathIdx);
					++nrPellets;
				}
				else if (type == "P")
				{
					scene.Add(CreatePowerPellet(x, y));
					pathIndices.insert(pathIdx);
					++nrPellets;
				}

				x += m_cellsize;
				pathIdx++;
			}
			y += m_cellsize;
			x = 0;
		}
		iFile.close();
	}
	else
	{
		std::cerr << "Can't open file " << filename << "\n";
	}

	// Give the graph all walkable indices
	Graph::GetInstance().SetNeighbors(pathIndices);
	GamestateManager::GetInstance().SetTotalPellets(nrPellets);
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


