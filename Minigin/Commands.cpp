#include "Commands.h"
#include "GameObject.h"
#include "MoveComponent.h"



// MOVE
//********
void dae::Move::Execute(float elapsedSec)
{
	MoveComponent* move = GetGameObject()->GetComponent<MoveComponent>();
	if (move)
		move->Move(m_direction, elapsedSec);
}

