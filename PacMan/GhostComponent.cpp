#include "GhostComponent.h"
#include "../Minigin/SpriteComponent.h"
#include "TargetMoverComponent.h"
#include <iostream>
#include "GhostState.h"

pacman::GhostComponent::GhostComponent(dae::GameObject* owner, std::unique_ptr<GhostState> state):
	Component(owner),
	m_damage{ 1 },
	m_ghostState{std::move(state)}
{
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
		m_ghostState->OnExit(*this);
		m_ghostState = std::move(newState);
		m_ghostState->OnEnter(*this);
	}
}
