#include "GhostState.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/GameObject.h"
#include <iostream>
#include "TargetMoverComponent.h"



// CHASE
pacman::ChaseState::ChaseState(dae::SpriteComponent* spriteComp, TargetMoverComponent* moveComp):
	m_spriteComp{spriteComp},
	m_moveComp{moveComp}
{
	if (m_spriteComp == nullptr)
		std::cerr << "Missing spritecomponent reference\n";
}

pacman::GhostState* pacman::ChaseState::Update(float elapsedSec)
{
	m_moveComp->MoveToTarget(elapsedSec);
	return nullptr;
}

void pacman::ChaseState::OnEnter()
{
	m_spriteComp->SetRow(0);
}

// DIZZIED
pacman::DizziedState::DizziedState(dae::SpriteComponent* spriteComp, TargetMoverComponent* moveComp) :
	m_spriteComp{spriteComp},
	m_moveComp{moveComp}
{
	if (m_spriteComp == nullptr)
		std::cerr << "Missing spritecomponent reference\n";
}

pacman::GhostState* pacman::DizziedState::Update(float)
{
	// Code to return chase state if you are dizzied for too long
	return nullptr;
}

void pacman::DizziedState::OnEnter()
{
	m_spriteComp->SetRow(4);
}

// EYES
pacman::EyeState::EyeState(dae::SpriteComponent* spriteComp):
	m_spriteComp{spriteComp}
{
	if (m_spriteComp == nullptr)
		std::cerr << "Missing spritecomponent reference\n";
}

pacman::GhostState* pacman::EyeState::Update(float)
{
	return nullptr;
}

void pacman::EyeState::OnEnter()
{
}
