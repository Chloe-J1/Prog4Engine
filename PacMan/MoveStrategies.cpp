#include "MoveStrategies.h"
#include "TargetMoverComponent.h"
#include "PlayerMovement.h"

void pacman::MovementBase::OnEnter()
{
}

void pacman::MovementBase::Move(float)
{
}

void pacman::MovementBase::OnExit()
{
}

void pacman::MovementBase::Init(TargetMoverComponent* moveComp) // TODO: pass through context
{
	m_moveComp = moveComp;
}

// CHASE


void pacman::ChaseMovement::Move(float elapsedSec)
{
	m_moveComp->MoveToTarget(elapsedSec);
}

// CORNER


void pacman::CornerMovement::Move(float elapsedSec)
{
	m_moveComp->MoveFrontTarget(elapsedSec);
}


void pacman::SueMovement::Move(float elapsedSec)
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
}

// FLEE

void pacman::FleeMovement::Move(float elapsedSec)
{
	m_moveComp->MoveToTarget(elapsedSec);
}


// NON AI

void pacman::NonAIMovement::OnEnter()
{
	m_playerMovement->SetIsEnabled(true);
}

void pacman::NonAIMovement::OnExit()
{
	m_playerMovement->SetIsEnabled(false);
}

void pacman::NonAIMovement::Init(PlayerMovement* playerMovementComp)
{
	m_playerMovement = playerMovementComp;
}
