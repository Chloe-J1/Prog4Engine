#include "IndicatorSpawnComponent.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/RenderComponent.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/EventQueue.h"
#include "AutoKill.h"
#include "Events.h"
#include <iostream>

pacman::IndicatorSpawnComponent::IndicatorSpawnComponent(dae::GameObject* owner):
	Component(owner)
{
	dae::EventQueue::GetInstance().AddEventHandler(this);
}

pacman::IndicatorSpawnComponent::~IndicatorSpawnComponent()
{
	dae::EventQueue::GetInstance().RemoveEventHandler(this);
}

void pacman::IndicatorSpawnComponent::Notify(const dae::Event& event)
{
	if (event.id == "GHOST_VALUE_CALCULATED")
	{
		auto* arg = static_cast<ScoreArg*>(event.arg.get());
		m_scene.Add(CreateIndicator(arg->sender->GetWorldPosition(), arg->addedValue));
	}
}

std::unique_ptr<dae::GameObject> pacman::IndicatorSpawnComponent::CreateIndicator(const glm::vec2& spawnPos, int value)
{
	std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("ScoreIndicator.png");
	go->AddComponent<dae::SpriteComponent>(1,4);
	std::cout << value << "\n";
	if (value == 200)
	{
		go->GetComponent<dae::SpriteComponent>()->SetRow(1);
	}
	else if (value == 400)
	{
		go->GetComponent<dae::SpriteComponent>()->SetRow(2);
	}
	else if (value == 800)
	{
		go->GetComponent<dae::SpriteComponent>()->SetRow(3);
	}
	else if (value == 1600)
	{
		go->GetComponent<dae::SpriteComponent>()->SetRow(4);
	}
	go->AddComponent<AutoKill>(2.f);
	go->SetLocalPosition(spawnPos);
	return go;
}
