#include "Commands.h"
#include "GameObject.h"
#include "MoveComponent.h"

// BASE COMMAND
//********
dae::Command::Command(TriggerEvent eventType):
	m_eventType{eventType}
{
}

dae::TriggerEvent dae::Command::GetEventType()
{
	return m_eventType;
}

// MOVE
//********
void dae::Move::Execute()
{
	MoveComponent* move = GetGameObject()->GetComponent<MoveComponent>();
	if (move)
		move->Move(m_direction);
}

