#include "Commands.h"
#include "GameObject.h"



// MOVE
//********
void dae::Move::Execute(float elapsedSec)
{
	GetGameObject()->AddLocalPosition(m_direction * m_speed * elapsedSec);
}

