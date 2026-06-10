#pragma once
#include "../Minigin/GameObject.h"
#include "../Minigin/Scene.h"
#include "Graph.h"
#include <string>
#include <unordered_set>

namespace pacman
{
	class LevelLoader final
	{
	public:
		explicit LevelLoader() = default;
		
		void InitLevel(dae::Scene& scene, const std::string& levelname);
		void JsonToBin(const std::string& jsonFile, const std::string& levelname);
	private:
		float m_cellsize{(float)Graph::GetInstance().GetCellSize()};
		int m_nrRows{Graph::GetInstance().GetNrRows()};
		int m_nrCols{Graph::GetInstance().GetNrCols()};
		std::unordered_set<int> m_pathIndices;

		std::unique_ptr<dae::GameObject> CreatePellet(float x, float y);
		std::unique_ptr<dae::GameObject> CreatePowerPellet(float x, float y);

		void ParseBin(dae::Scene& scene, const std::string& levelname);
		void ParseJson(dae::Scene& scene, const std::string& levelname);
	};
}