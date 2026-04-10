#include "Commands.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

#include <iostream>

// MOVE
//********
void pacman::Move::Execute()
{
	m_moveComp->Move(m_direction);
}

