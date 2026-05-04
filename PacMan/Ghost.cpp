#include "Ghost.h"
#include "../Minigin/SpriteComponent.h"

pacman::GhostComponent::GhostComponent(dae::GameObject* owner, dae::GameObject* targetObj):
	Component(owner),
	m_damage{ 1 }
{
	m_ghostState = new ChaseState(GetGameObject(), GetGameObject()->GetComponent<dae::SpriteComponent>(), targetObj);
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
