#include "GhostState.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/GameObject.h"
#include "TargetMoverComponent.h"
#include "../Minigin/EventQueue.h"
#include "GhostComponent.h"
#include "Events.h"
#include "../Minigin/Hitbox.h"
#include "MoveStrategies.h"


// FOLLOW TARGET

std::unique_ptr<pacman::GhostState> pacman::FollowTargetState::Update(GhostComponent&, float elapsedSec)
{
	m_moveStrategy->Move(elapsedSec);
	return nullptr;
}

void pacman::FollowTargetState::OnEnter(GhostComponent& ghost)
{
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->ChangeCurrentAnimation(0, 1);
	m_moveStrategy = ghost.GetMoveStrategy();
	m_moveStrategy->OnEnter();
}

std::unique_ptr<pacman::GhostState> pacman::FollowTargetState::Notify(pacman::GhostComponent&, dae::GameObject*, const dae::Event& event)
{
	if (event.id == "POWER_PELLET_PICKUP")
	{
		return std::make_unique<DizziedState>();
	}
	return nullptr;
}

void pacman::FollowTargetState::OnExit(pacman::GhostComponent&)
{
	m_moveStrategy->OnExit();
}

// DIZZIED
std::unique_ptr<pacman::GhostState> pacman::DizziedState::Update(pacman::GhostComponent&,float elapsedSec)
{
	m_moveComp->MoveAwayTarget(elapsedSec);

	// Timer
	m_dizziedTime += elapsedSec;
	if (m_dizziedTime >= m_maxDizziedTime)
	{
		return std::make_unique<FollowTargetState>();
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
}

void pacman::DizziedState::OnExit(pacman::GhostComponent& ghost)
{
	if (m_dizziedTime >= m_maxDizziedTime) // ALL ghost are no longer in the dizzied state
	{
		dae::Event event = dae::Event{ "NOT_DIZZIED" };
		dae::EventQueue::GetInstance().Invoke(std::move(event), ghost.GetGameObject());
	}
	m_dizziedTime = 0;
}

std::unique_ptr<pacman::GhostState> pacman::DizziedState::Notify(pacman::GhostComponent& , dae::GameObject*, const dae::Event& event)
{
	if (event.id == "GHOST_DIED")
	{
		auto* arg = static_cast<GhostDiedArg*>(event.arg.get());
		if (arg->ghost == m_ghost)
		{
			return std::make_unique<EyeState>();
		}
	}
	return nullptr;
}

// EYES
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


