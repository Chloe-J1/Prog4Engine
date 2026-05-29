#include "GhostState.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/GameObject.h"
#include "TargetMoverComponent.h"
#include "../Minigin/EventQueue.h"
#include "GhostComponent.h"
#include "Events.h"
#include "../Minigin/Hitbox.h"
#include "MoveStrategies.h"

void pacman::GhostState::OnEnter(GhostComponent&)
{
}

std::unique_ptr<pacman::GhostState> pacman::GhostState::Update(pacman::GhostComponent&, float)
{
	return nullptr;
}

std::unique_ptr<pacman::GhostState> pacman::GhostState::Notify(pacman::GhostComponent&, dae::GameObject*, const dae::Event& event)
{
	if (event.id == "PLAYER_TAKES_DAMAGE")
	{
		return std::make_unique<DeathState>();
	}
	return nullptr;
}

void pacman::GhostState::OnExit(pacman::GhostComponent&)
{
}

// FOLLOW TARGET
void pacman::FollowTargetState::OnEnter(GhostComponent& ghost)
{
	m_spriteComp = ghost.GetGameObject()->GetComponent<dae::SpriteComponent>();
	m_spriteComp->ChangeCurrentAnimation(0, 1);
	m_moveStrategy = ghost.GetMoveStrategy();
	m_moveStrategy->OnEnter();
}

std::unique_ptr<pacman::GhostState> pacman::FollowTargetState::Update(GhostComponent&, float elapsedSec)
{
	m_moveStrategy->Move(elapsedSec);
	return nullptr;
}



std::unique_ptr<pacman::GhostState> pacman::FollowTargetState::Notify(pacman::GhostComponent& ghost, dae::GameObject* sender, const dae::Event& event)
{
	auto state = GhostState::Notify(ghost, sender, event);
	if (state != nullptr) return state;

	if (event.id == "POWER_PELLET_PICKUP")
	{
		return std::make_unique<DizziedState>();
	}
	else if (event.id == "DIRECTION_CHANGED" && sender == ghost.GetGameObject())
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
	return nullptr;
}

void pacman::FollowTargetState::OnExit(pacman::GhostComponent&)
{
	m_moveStrategy->OnExit();
}

// DIZZIED
void pacman::DizziedState::OnEnter(pacman::GhostComponent& ghost)
{
	m_ghost = ghost.GetGameObject();
	m_moveComp = ghost.GetGameObject()->GetComponent<pacman::TargetMoverComponent>();
	m_spriteComp = ghost.GetGameObject()->GetComponent<dae::SpriteComponent>();
	m_spriteComp->ChangeCurrentAnimation(4, 1);

	m_moveStrategy = ghost.GetMoveStrategy();
	if (dynamic_cast<pacman::NonAIMovement*>(m_moveStrategy))
	{
		m_isNonAIStrategy = true;
	}
	m_moveStrategy->OnEnter();
}

std::unique_ptr<pacman::GhostState> pacman::DizziedState::Update(pacman::GhostComponent&,float elapsedSec)
{
	if(not m_isNonAIStrategy)
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
	
	return nullptr;
}

std::unique_ptr<pacman::GhostState> pacman::DizziedState::Notify(pacman::GhostComponent& ghost, dae::GameObject* sender, const dae::Event& event)
{
	auto state = GhostState::Notify(ghost, sender, event);
	if (state != nullptr) return state;
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

void pacman::DizziedState::OnExit(pacman::GhostComponent& ghost)
{
	if (m_dizziedTime >= m_maxDizziedTime) // ALL ghost are no longer in the dizzied state
	{
		dae::Event event = dae::Event{ "NOT_DIZZIED" };
		dae::EventQueue::GetInstance().Invoke(std::move(event), ghost.GetGameObject());
	}
	m_dizziedTime = 0;

	m_moveStrategy->OnExit();
}

// EYES

void pacman::EyeState::OnEnter(GhostComponent& ghost)
{
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->ChangeCurrentAnimation(6, 1);
	m_moveComp = ghost.GetGameObject()->GetComponent<pacman::TargetMoverComponent>();
	m_hitbox = ghost.GetGameObject()->GetComponent<dae::Hitbox>();
	m_hitbox->SetIsEnabled(false);
}

std::unique_ptr<pacman::GhostState> pacman::EyeState::Update(pacman::GhostComponent& ,float elapsedSec)
{
	if (m_moveComp->MoveToCell(m_targetIdx, elapsedSec))
	{
		return std::make_unique<DeathState>();
	}

	return nullptr;
}

void pacman::EyeState::OnExit(GhostComponent&)
{
	m_hitbox->SetIsEnabled(true);
}

// DEATH
void pacman::DeathState::OnEnter(GhostComponent& ghost)
{
	// Move to center box
	ghost.GetGameObject()->GetTransform().SetLocalPosition(Graph::GetInstance().GetWorldPos(m_centerBoxIdx));
	ghost.GetGameObject()->GetComponent<dae::SpriteComponent>()->ChangeCurrentAnimation(0,1);
	m_moveComp = ghost.GetGameObject()->GetComponent<pacman::TargetMoverComponent>();
}

std::unique_ptr<pacman::GhostState> pacman::DeathState::Update(GhostComponent&, float elapsedSec)
{
	m_timer += elapsedSec;
	if (m_timer >= m_maxDeathTime)
	{
		return std::make_unique<pacman::FollowTargetState>();
	}
	m_moveComp->Wander(elapsedSec);
	return std::unique_ptr<pacman::GhostState>();
}

void pacman::DeathState::OnExit(GhostComponent& ghost)
{
	ghost.GetGameObject()->SetLocalPosition(m_respawnPos);
}


