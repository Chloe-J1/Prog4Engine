#include "FruitSpawner.h"
#include "../Minigin/Hitbox.h"
#include "../Minigin/RenderComponent.h"
#include "FruitComponent.h"
#include "../Minigin/SpriteComponent.h"
#include "TargetMoverComponent.h"

pacman::FruitSpawner::FruitSpawner(dae::GameObject* owner, dae::Scene* scene) :
	dae::Component(owner),
	m_scene{ scene }
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

pacman::FruitSpawner::~FruitSpawner()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

std::unique_ptr<dae::GameObject> pacman::FruitSpawner::CreateFruit()
{
	std::unique_ptr<dae::GameObject> fruit = std::make_unique<dae::GameObject>();
	std::string spriteFilename{ "Fruit.png" };
	fruit->SetLocalPosition(m_spawnPos);
	const int size{ 16 };
	const int nrCols{ 1 };
	const int nrRows{ 3 };
	fruit->AddComponent<dae::Hitbox>(size, size);
	fruit->AddComponent<dae::RenderComponent>(spriteFilename);
	fruit->AddComponent<dae::SpriteComponent>(nrCols, nrRows);
	fruit->AddComponent<pacman::FruitComponent>();
	fruit->AddComponent<pacman::TargetMoverComponent>();

	// Random fruit appearance
	fruit->GetComponent<dae::SpriteComponent>()->SetRow(rand() % nrRows);
	
	return fruit;
}

void pacman::FruitSpawner::SpawnFruit()
{
	m_scene->Add(CreateFruit());
}

void pacman::FruitSpawner::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "PELLET_PICKUP" || event.id == "POWER_PELLET_PICKUP")
	{
		++m_nrPelletsPickedup;
		if (m_nrPelletsPickedup >= m_nrPelletsForFruitSpawn)
		{
			m_nrPelletsPickedup = 0;
			SpawnFruit();
		}
	}
}
