#include "GhostState.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/GameObject.h"
#include <iostream>
#include "TargetMoverComponent.h"
#include "../Minigin/EventQueue.h"



// CHASE
pacman::ChaseState::ChaseState(dae::SpriteComponent* spriteComp, TargetMoverComponent* moveComp):
	m_spriteComp{spriteComp},
	m_moveComp{moveComp}
{
	if (m_spriteComp == nullptr)
		std::cerr << "Missing spritecomponent reference\n";

	dae::EventQueue::GetInstance().AddObserver(this);
}

std::unique_ptr<pacman::GhostState> pacman::ChaseState::Update(float elapsedSec)
{
	m_moveComp->MoveToTarget(elapsedSec);
	return std::move(m_returnedState);
}

void pacman::ChaseState::OnEnter()
{
	m_spriteComp->SetRow(0);
	m_returnedState = nullptr;
}

void pacman::ChaseState::OnExit()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::ChaseState::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "POWER_PELLET_PICKUP")
	{
		std::cout << "power pellet pickup!\n";
		m_returnedState =  std::make_unique<DizziedState>(m_spriteComp, m_moveComp);
	}
}

// DIZZIED
pacman::DizziedState::DizziedState(dae::SpriteComponent* spriteComp, TargetMoverComponent* moveComp) :
	m_spriteComp{spriteComp},
	m_moveComp{moveComp}
{
	if (m_spriteComp == nullptr)
		std::cerr << "Missing spritecomponent reference\n";
}

std::unique_ptr<pacman::GhostState> pacman::DizziedState::Update(float elapsedSec)
{
	m_dizziedTime += elapsedSec;
	if (m_dizziedTime >= m_maxDizziedTime)
	{
		return std::make_unique<ChaseState>(m_spriteComp, m_moveComp);
	}
	return nullptr;
}

void pacman::DizziedState::OnEnter()
{
	m_spriteComp->SetRow(4);
}

void pacman::DizziedState::OnExit()
{
	m_dizziedTime = 0;
}

// EYES
pacman::EyeState::EyeState(dae::SpriteComponent* spriteComp):
	m_spriteComp{spriteComp}
{
	if (m_spriteComp == nullptr)
		std::cerr << "Missing spritecomponent reference\n";
}

std::unique_ptr<pacman::GhostState> pacman::EyeState::Update(float)
{
	return nullptr;
}

void pacman::EyeState::OnEnter()
{
}
