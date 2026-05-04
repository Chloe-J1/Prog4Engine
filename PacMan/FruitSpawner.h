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
		FruitSpawner(dae::GameObject* owner, dae::Scene* scene) :
			dae::Component(owner),
			m_scene{scene}
		{
			dae::EventQueue::GetInstance().AddObserver(this);
			SpawnFruit();
		}
		~FruitSpawner()
		{
			dae::EventQueue::GetInstance().RemoveObserver(this);
		}
		FruitSpawner(const FruitSpawner& other) = delete;
		FruitSpawner(FruitSpawner&& other) = delete;
		FruitSpawner& operator=(const FruitSpawner& otehr) = delete;
		FruitSpawner& operator=(FruitSpawner&& otehr) = delete;

	private:
		std::unique_ptr<dae::GameObject> CreateFruit()
		{
			std::unique_ptr<dae::GameObject> fruit = std::make_unique<dae::GameObject>();
			glm::vec2 spawnPos{ 24,24 };
			std::string spriteFilename{ "Fruit.png" };
			fruit->SetLocalPosition(spawnPos.x, spawnPos.y);
			const int size{ 16 };
			const int nrCols{ 1 };
			const int nrRows{ 3 };
			fruit->AddComponent<dae::Hitbox>(size, size);
			fruit->AddComponent<dae::RenderComponent>(spriteFilename);
			fruit->AddComponent<dae::SpriteComponent>(nrCols, nrRows);
			fruit->AddComponent<pacman::FruitComponent>();
			return fruit;
		}

		void SpawnFruit()
		{
			m_scene->Add(CreateFruit());
		}

		virtual void Notify(dae::GameObject*, const dae::Event& event)
		{
			if (event.id == "PELLET_PICKUP")
			{
				++m_nrPelletsPickedup;
				if (m_nrPelletsPickedup >= m_nrPelletsForFruitSpawn)
				{
					m_nrPelletsPickedup = 0;
					//SpawnFruit();
				}
			}
		}
		dae::Scene* m_scene{};
		int m_nrPelletsPickedup{ 5 }; // 64
		const int m_nrPelletsForFruitSpawn{ 5 };
	};
}