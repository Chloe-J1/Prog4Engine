#include "LevelLoader.h"
#include <sstream>
#include <fstream>
#include <string>
#include "../Minigin/RenderComponent.h"
#include "../Minigin/Hitbox.h"

#include "Pellets.h"

void pacman::LevelLoader::ReadLevel(dae::Scene& scene, const std::string& filename)
{
	std::ifstream iFile;
	iFile.open(filename);
	std::string line;
	float x{};
	float y{};
	float size{ 24.f };

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
					scene.Add(CreateWall(x, y));
				}
				else if (type == "p")
				{
					scene.Add(CreatePellet(x, y));
				}
				x += size;
			}
			y += size;
			x = 0;
		}
		iFile.close();
	}
	else
	{
		throw std::invalid_argument("this file can't be opened");
	}
}

std::unique_ptr<dae::GameObject> pacman::LevelLoader::CreateWall(float x, float y)
{
	std::unique_ptr<dae::GameObject> wall = std::make_unique <dae::GameObject>();
	wall->AddComponent<dae::RenderComponent>("Wall_24.png");
	wall->AddComponent<dae::Hitbox>(24, 24);
	wall->SetLocalPosition(x, y);
	wall->SetLayer("Obstacle");
	return wall;
}

std::unique_ptr<dae::GameObject> pacman::LevelLoader::CreatePellet(float x, float y)
{
	const int offset{ 10 };
	std::unique_ptr<dae::GameObject> pellet = std::make_unique<dae::GameObject>();
	pellet->AddComponent<dae::Hitbox>(4, 4);
	pellet->AddComponent<dae::RenderComponent>("Pellet_small.png");
	pellet->AddComponent<pacman::SmallPellet>();
	pellet->SetLocalPosition(x + offset, y + offset);
	return pellet;
}

