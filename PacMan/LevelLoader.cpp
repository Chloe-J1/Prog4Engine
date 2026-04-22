#include "LevelLoader.h"
#include <sstream>
#include <fstream>
#include <string>
#include "../Minigin/RenderComponent.h"
#include "../Minigin/Hitbox.h"

#include "Pellets.h"

#include <iostream>
void pacman::LevelLoader::InitLevel(dae::Scene& scene, const std::string& filename)
{
	std::ifstream iFile;
	iFile.open(filename);
	std::string line;
	float x{};
	float y{};
	float wallStartX{ -1.f };
	int wallWidth{ 0 };

	if (iFile.is_open())
	{
		while (std::getline(iFile, line))
		{
			std::stringstream ss(line);
			std::string type;

			while (std::getline(ss, type, ','))
			{
				if (type == "w")
				{
					if (wallStartX < 0.f)
						wallStartX = x;
					wallWidth += (int)m_cellsize;  
				}
				else
				{
					if (wallStartX >= 0.f)
					{
						scene.Add(CreateWall(wallStartX, y, wallWidth));
						wallStartX = -1.f;
						wallWidth = 0;
					}

					if (type == "p")
						scene.Add(CreatePellet(x, y));
				}
				// Reset wall values
				if (wallStartX >= 0.f)
				{
					scene.Add(CreateWall(wallStartX, y, wallWidth));
					wallStartX = -1.f;
					wallWidth = 0;
				}

				x += m_cellsize;
			}
			y += m_cellsize;
			x = 0;
		}
		iFile.close();
	}
	else
	{
		throw std::invalid_argument("this file can't be opened");
	}
}

std::unique_ptr<dae::GameObject> pacman::LevelLoader::CreateWall(float x, float y, int width)
{
	constexpr int height{ 24 };
	std::unique_ptr<dae::GameObject> wall = std::make_unique <dae::GameObject>();
	wall->AddComponent<dae::Hitbox>(width, height);
	wall->SetLocalPosition(x, y);
	wall->SetLayer("Obstacle");
	return wall;
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

