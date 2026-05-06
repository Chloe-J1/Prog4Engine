#include "GhostState.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/GameObject.h"
#include <iostream>
#include "TargetMoverComponent.h"
#include "../Minigin/EventQueue.h"
#include "GhostComponent.h"

#include <iostream>
// CHASE
pacman::ChaseState::ChaseState()
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

std::unique_ptr<pacman::GhostState> pacman::ChaseState::Update(float elapsedSec)
{
	m_moveComp->MoveToTarget(elapsedSec);
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
		m_returnedState =  std::make_unique<DizziedState>();
	}
}

// CORNER
pacman::CornerState::CornerState()
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

std::unique_ptr<pacman::GhostState> pacman::CornerState::Update(float elapsedSec)
{
	m_moveComp->MoveFrontTarget(elapsedSec);
	return std::move(m_returnedState);
}

void pacman::CornerState::OnEnter(GhostComponent& ghost)
{
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->SetRow(0);
	m_moveComp = ghost.GetGameObject()->GetComponent<pacman::TargetMoverComponent>();
	m_returnedState = nullptr;
}

void pacman::CornerState::OnExit(pacman::GhostComponent&)
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::CornerState::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "POWER_PELLET_PICKUP")
	{
		m_returnedState = std::make_unique<DizziedState>();
	}
}

// SUE
pacman::SueState::SueState()
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

std::unique_ptr<pacman::GhostState> pacman::SueState::Update(float elapsedSec)
{
	m_fleeTimer += elapsedSec;
	if (m_fleeTimer >= m_maxTime)
	{
		m_isFleeing = !m_isFleeing;
		m_fleeTimer = 0;
	}
	if (m_isFleeing)
	{
		m_moveComp->MoveAwayTarget(elapsedSec);
	}
	else
	{
		m_moveComp->MoveToTarget(elapsedSec);
	}


	return std::move(m_returnedState);
}

void pacman::SueState::OnEnter(GhostComponent& ghost)
{
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->SetRow(0);
	m_moveComp = ghost.GetGameObject()->GetComponent<pacman::TargetMoverComponent>();
	m_returnedState = nullptr;
}

void pacman::SueState::OnExit(pacman::GhostComponent&)
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::SueState::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "POWER_PELLET_PICKUP")
	{
		m_returnedState = std::make_unique<DizziedState>();
	}
}

// DIZZIED
std::unique_ptr<pacman::GhostState> pacman::DizziedState::Update(float elapsedSec)
{
	m_moveComp->MoveAwayTarget(elapsedSec);

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


