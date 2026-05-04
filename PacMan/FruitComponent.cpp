#include "FruitComponent.h"

#include <iostream>

int pacman::FruitComponent::m_nrFruit{};

pacman::FruitComponent::FruitComponent(dae::GameObject* owner):
	dae::Component(owner),
	m_windowWidth{ dae::WindowConfig::GetInstance().GetWidth() },
	m_windowHeight{ dae::WindowConfig::GetInstance().GetHeight() }
{
}

void pacman::FruitComponent::OnCollision(dae::GameObject* other)
{
	if (other->GetLayer() == "Player")
	{
		// Fruit pickup event
		std::cout << "pickup fruit\n";
		// Move to bottom right pos based on nrfruit
		glm::vec2 spawnPos{ m_windowWidth, m_windowHeight };
		const float offset{ 2.f };
		const float spacing{ 20.f };
		spawnPos -= offset;
		spawnPos.x -= spacing * m_nrFruit - 1;
		spawnPos.y -= spacing;
		GetGameObject()->SetLocalPosition(spawnPos.x, spawnPos.y);

		// TODO: increase score
	}
}
