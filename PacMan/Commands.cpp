#include "Commands.h"
#include "../Minigin/EventQueue.h"
#include <memory>
// MOVE
//********
void pacman::Move::Execute()
{
	m_moveComp->Move(m_direction);

	Event directionChangedEvent{ EventId::DIRECTION_CHANGED };
	directionChangedEvent.arg = std::make_unique<DirectionChangedArg>(m_direction);
	dae::EventQueue::GetInstance().Invoke(std::move(directionChangedEvent), GetGameObject());
}

