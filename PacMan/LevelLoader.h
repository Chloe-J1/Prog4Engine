#pragma once
#include "../Minigin/GameObject.h"
#include "../Minigin/Scene.h"

namespace pacman
{
	class LevelLoader final
	{
	public:
		explicit LevelLoader() = default;
		
		void InitLevel(dae::Scene& scene, const std::string& filename);
	private:
		float m_cellsize{ 24.f };

		std::unique_ptr<dae::GameObject> CreateWall(float x, float y, int width);
		std::unique_ptr<dae::GameObject> CreatePellet(float x, float y);
	};
}