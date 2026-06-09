#pragma once
#include "../Minigin/EventQueue.h"
#include "../Minigin/Component.h"
#include "../Minigin/Scene.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/IEventHandler.h"
#include "Graph.h"
#include <glm/glm.hpp>

namespace pacman
{
	class FruitSpawner final : public dae::Component, public dae::IEventHandler
	{
	public:
		FruitSpawner(dae::GameObject* owner, dae::Scene* scene);
		~FruitSpawner();
		FruitSpawner(const FruitSpawner& other) = delete;
		FruitSpawner(FruitSpawner&& other) = delete;
		FruitSpawner& operator=(const FruitSpawner& other) = delete;
		FruitSpawner& operator=(FruitSpawner&& other) = delete;

	private:

		std::unique_ptr<dae::GameObject> CreateFruit();
		void SpawnFruit();
		void Notify(const dae::Event& event);


		dae::Scene* m_scene{};
		int m_nrPelletsPickedup{ 0 };
		const int m_nrPelletsForFruitSpawn{ 70 };
		glm::vec2 m_spawnPos{ Graph::GetInstance().GetWorldPos(542) };
	};
}