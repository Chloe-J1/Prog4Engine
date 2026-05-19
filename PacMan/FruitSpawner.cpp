#include "FruitSpawner.h"

pacman::FruitSpawner::FruitSpawner(dae::GameObject* owner, dae::Scene* scene) :
	dae::Component(owner),
	m_scene{ scene }
{
	dae::EventQueue::GetInstance().AddObserver(this);
	SpawnFruit();
}

pacman::FruitSpawner::~FruitSpawner()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

std::unique_ptr<dae::GameObject> pacman::FruitSpawner::CreateFruit()
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

void pacman::FruitSpawner::SpawnFruit()
{
	m_scene->Add(CreateFruit());
}

void pacman::FruitSpawner::Notify(dae::GameObject*, const dae::Event& event)
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
