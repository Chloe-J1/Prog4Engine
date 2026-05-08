#include "MoveStrategies.h"
#include "TargetMoverComponent.h"

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

void pacman::MovementBase::Init(TargetMoverComponent* moveComp)
{
	m_moveComp = moveComp;
}
