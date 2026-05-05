#include "GhostState.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/GameObject.h"
#include <iostream>
#include "TargetMoverComponent.h"
#include "../Minigin/EventQueue.h"
#include "Ghost.h"

#include <iostream>
// CHASE
pacman::ChaseState::ChaseState()
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

std::unique_ptr<pacman::GhostState> pacman::ChaseState::Update(float elapsedSec)
{
	m_moveComp->MoveToTarget(elapsedSec, false);
	return std::move(m_returnedState);
}

void pacman::ChaseState::OnEnter(pacman::GhostComponent& ghost)
{
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->SetRow(0);
	m_moveComp = ghost.GetGameObject()->GetComponent<pacman::TargetMoverComponent>();
	m_returnedState = nullptr;
}

void pacman::ChaseState::OnExit(pacman::GhostComponent&)
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::ChaseState::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "POWER_PELLET_PICKUP")
	{
		std::cout << "power pellet pickup!\n";
		m_returnedState =  std::make_unique<DizziedState>();
	}
}

// DIZZIED


std::unique_ptr<pacman::GhostState> pacman::DizziedState::Update(float elapsedSec)
{
	m_moveComp->MoveToTarget(elapsedSec, true);

	// Timer
	m_dizziedTime += elapsedSec;
	if (m_dizziedTime >= m_maxDizziedTime)
	{
		return std::make_unique<ChaseState>();
	}
	return nullptr;
}

void pacman::DizziedState::OnEnter(pacman::GhostComponent& ghost)
{
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->SetRow(4);
	m_moveComp = ghost.GetGameObject()->GetComponent<pacman::TargetMoverComponent>();
}

void pacman::DizziedState::OnExit(pacman::GhostComponent& ghost)
{
	m_dizziedTime = 0;
	dae::Event event = dae::Event{ "NOT_DIZZIED" };
	dae::EventQueue::GetInstance().Invoke(std::move(event), ghost.GetGameObject());
}

// EYES
pacman::EyeState::EyeState()	
{
}

std::unique_ptr<pacman::GhostState> pacman::EyeState::Update(float)
{
	return nullptr;
}

void pacman::EyeState::OnEnter(GhostComponent&)
{
}


