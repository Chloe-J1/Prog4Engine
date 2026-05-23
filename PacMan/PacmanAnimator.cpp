#include "PacmanAnimator.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/EventQueue.h"
#include "../Minigin/SpriteComponent.h"
#include "Events.h"

pacman::PacmanAnimator::PacmanAnimator(dae::GameObject* owner) :
	Component(owner),
	m_spriteComp{GetGameObject()->GetComponent<dae::SpriteComponent>()}
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

pacman::PacmanAnimator::~PacmanAnimator()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::PacmanAnimator::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "DIRECTION_CHANGED")
	{
		DirectionChangedArg* arg{ static_cast<pacman::DirectionChangedArg*>(event.arg.get()) };
		if (arg->direction.x == 1) // right
		{
			m_spriteComp->SetRow(0);
		}
		else if (arg->direction.x == -1) // left
		{
			m_spriteComp->SetRow(1);
		}
		else if (arg->direction.y == -1) // up
		{
			m_spriteComp->SetRow(2);
		}
		else // down
		{
			m_spriteComp->SetRow(3);
		}
	}
}
