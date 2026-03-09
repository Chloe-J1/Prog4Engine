#include "Commands.h"
#include "GameObject.h"
#include "MoveComponent.h"


void dae::Move::Execute()
{
	MoveComponent* move = GetGameObject()->GetComponent<MoveComponent>();
	if (move)
		move->Move(m_direction);
}
