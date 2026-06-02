#pragma once
#include "../Minigin/GameObject.h"
#include "../Minigin/Scene.h"
#include "Graph.h"
#include <string>

namespace pacman
{
	class LevelLoader final
	{
	public:
		explicit LevelLoader() = default;
		
		void InitLevel(dae::Scene& scene, const std::string& filename, const std::string& levelname);
	private:
		float m_cellsize{(float)Graph::GetInstance().GetCellSize()};

		std::unique_ptr<dae::GameObject> CreatePellet(float x, float y);
		std::unique_ptr<dae::GameObject> CreatePowerPellet(float x, float y);
	};
}