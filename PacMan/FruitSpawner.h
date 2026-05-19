#pragma once
#include "../Minigin/EventQueue.h"
#include "../Minigin/Component.h"
#include "../Minigin/Scene.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/Hitbox.h"
#include "../Minigin/RenderComponent.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/Observer.h"
#include "../Minigin/SceneManager.h"
#include <glm/glm.hpp>
#include "FruitComponent.h"
#include "Events.h"
#include "Pellets.h"


namespace pacman
{
	class FruitSpawner final : public dae::Component, public dae::Observer
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
		virtual void Notify(dae::GameObject*, const dae::Event& event);


		dae::Scene* m_scene{};
		int m_nrPelletsPickedup{ 5 }; // 64
		const int m_nrPelletsForFruitSpawn{ 5 };
	};
}