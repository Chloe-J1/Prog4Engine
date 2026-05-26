#include "FruitComponent.h"

#include "../Minigin/WindowConfig.h"
#include <string>
#include <glm/glm.hpp>
#include "../Minigin/SpriteComponent.h"
#include "TargetMoverComponent.h"


int pacman::FruitComponent::m_nrFruit{};

pacman::FruitComponent::FruitComponent(dae::GameObject* owner):
	dae::Component(owner),
	m_windowWidth{ dae::WindowConfig::GetInstance().GetWidth() },
	m_windowHeight{ dae::WindowConfig::GetInstance().GetHeight()},
	m_spriteWidth{GetGameObject()->GetComponent<dae::SpriteComponent>()->GetWidth()}
{
}

void pacman::FruitComponent::Start()
{
	m_moveComp = GetGameObject()->GetComponent<pacman::TargetMoverComponent>();
}

int pacman::FruitComponent::GetValue() const
{
	return m_value;
}

void pacman::FruitComponent::OnCollision(dae::GameObject* other)
{
	if (other->GetLayer() == "Player")
	{
		// Move to bottom right pos based on nrfruit
		glm::vec2 spawnPos{ m_windowWidth, m_windowHeight };
		const float offset{ 2.f };
		const float spacing{ 20.f };
		spawnPos -= offset;
		spawnPos.x -= (spacing * m_nrFruit + 1 * m_spriteWidth);
		spawnPos.y -= spacing;
		GetGameObject()->SetLocalPosition(spawnPos.x, spawnPos.y);
		++m_nrFruit;

		this->SetIsEnabled(false);
	}
}

void pacman::FruitComponent::Update(float elapsecSec)
{
	m_moveComp->Wander(elapsecSec);
}
