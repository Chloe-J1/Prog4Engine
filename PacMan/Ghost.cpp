#include "Ghost.h"
#include "../Minigin/SpriteComponent.h"
#include "TargetMoverComponent.h"
#include <iostream>

pacman::GhostComponent::GhostComponent(dae::GameObject* owner):
	Component(owner),
	m_damage{ 1 }
{
	m_ghostState = new ChaseState(GetGameObject()->GetComponent<dae::SpriteComponent>(), GetGameObject()->GetComponent<pacman::TargetMoverComponent>());
}

int pacman::GhostComponent::GetDamage() const
{
	return m_damage;
}

void pacman::GhostComponent::Update(float elapsedSec)
{
	auto newState{ m_ghostState->Update(elapsedSec) };
	if (newState != nullptr)
	{
		m_ghostState = newState;
	}
}
