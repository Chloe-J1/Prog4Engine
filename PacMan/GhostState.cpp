#include "GhostState.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/GameObject.h"
#include "TargetMoverComponent.h"
#include "../Minigin/EventQueue.h"
#include "GhostComponent.h"
#include "Events.h"
#include "../Minigin/Hitbox.h"

// CHASE
pacman::ChaseState::ChaseState()
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

std::unique_ptr<pacman::GhostState> pacman::ChaseState::Update(pacman::GhostComponent& ,float elapsedSec)
{
	m_moveComp->MoveToTarget(elapsedSec);
	return std::move(m_returnedState);
}

void pacman::ChaseState::OnEnter(pacman::GhostComponent& ghost)
{
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->ChangeCurrentAnimation(0,1);
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

std::unique_ptr<pacman::GhostState> pacman::CornerState::Update(pacman::GhostComponent& ,float elapsedSec)
{
	m_moveComp->MoveFrontTarget(elapsedSec);
	return std::move(m_returnedState);
}

void pacman::CornerState::OnEnter(GhostComponent& ghost)
{
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->ChangeCurrentAnimation(0,1);
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

std::unique_ptr<pacman::GhostState> pacman::SueState::Update(pacman::GhostComponent& ,float elapsedSec)
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
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->ChangeCurrentAnimation(0,1);
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
std::unique_ptr<pacman::GhostState> pacman::DizziedState::Update(pacman::GhostComponent&,float elapsedSec)
{
	m_moveComp->MoveAwayTarget(elapsedSec);

	// Timer
	m_dizziedTime += elapsedSec;
	if (m_dizziedTime >= m_maxDizziedTime)
	{
		return std::make_unique<ChaseState>();
	}
	else if (m_dizziedTime >= m_almostDoneTime)
	{
		m_spriteComp->ChangeCurrentAnimation(5, 2);
	}
	
	return std::move(m_returnedState);
}

void pacman::DizziedState::OnEnter(pacman::GhostComponent& ghost)
{
	m_ghost = ghost.GetGameObject();
	m_moveComp = ghost.GetGameObject()->GetComponent<pacman::TargetMoverComponent>();
	m_spriteComp = ghost.GetGameObject()->GetComponent<dae::SpriteComponent>();
	m_spriteComp->ChangeCurrentAnimation(4, 1);
	dae::EventQueue::GetInstance().AddObserver(this);
}

void pacman::DizziedState::OnExit(pacman::GhostComponent& ghost)
{
	m_dizziedTime = 0;
	dae::Event event = dae::Event{ "NOT_DIZZIED" };
	dae::EventQueue::GetInstance().Invoke(std::move(event), ghost.GetGameObject());
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::DizziedState::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "GHOST_DIED")
	{
		auto* arg = static_cast<GhostDiedArg*>(event.arg.get());
		if (arg->ghost == m_ghost)
		{
			m_returnedState = std::make_unique<EyeState>();
		}
	}
}

// EYES
pacman::EyeState::EyeState()	
{
}

std::unique_ptr<pacman::GhostState> pacman::EyeState::Update(pacman::GhostComponent& ,float elapsedSec)
{
	if (m_moveComp->MoveToCell(m_targetIdx, elapsedSec))
	{
		return std::make_unique<IdleState>();
	}

	return nullptr;
}

void pacman::EyeState::OnEnter(GhostComponent& ghost)
{
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->ChangeCurrentAnimation(6,1);
	m_moveComp = ghost.GetGameObject()->GetComponent<pacman::TargetMoverComponent>();
	m_hitbox = ghost.GetGameObject()->GetComponent<dae::Hitbox>();
	m_hitbox->SetIsEnabled(false);
}

void pacman::EyeState::OnExit(GhostComponent&)
{
	m_hitbox->SetIsEnabled(true);
}

// IDLE
void pacman::IdleState::OnEnter(GhostComponent& ghost)
{
	// Move to center box
	ghost.GetGameObject()->GetTransform().SetLocalPosition(Graph::GetInstance().GetWorldPos(m_centerBoxIdx));
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->ChangeCurrentAnimation(0,1);
}
