#include "Ghost.h"
#include "../Minigin/SpriteComponent.h"
#include "TargetMoverComponent.h"
#include <iostream>
#include "GhostState.h"

pacman::GhostComponent::GhostComponent(dae::GameObject* owner):
	Component(owner),
	m_damage{ 1 }
{
	m_ghostState = std::make_unique<ChaseState>();
	m_ghostState->OnEnter(*this);
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
		m_ghostState->OnExit();
		m_ghostState = std::move(newState);
		m_ghostState->OnEnter(*this);
	}
}
