#include "GhostComponent.h"
#include "GhostState.h"
#include "../Minigin/EventQueue.h"
#include "TargetMoverComponent.h"
#include "../Minigin/SceneManager.h"
#include "HealthComponent.h"

pacman::GhostComponent::GhostComponent(dae::GameObject* owner, std::unique_ptr<MovementBase> moveStrategy):
	Component(owner),
	m_damage{ 1 },
	m_ghostState{std::make_unique<FollowTargetState>()},
	m_moveStrategy{std::move(moveStrategy)}
{
	m_ghostState->OnEnter(*this);
	dae::EventQueue::GetInstance().AddObserver(this);
	m_moveStrategy->Init(GetGameObject()->GetComponent<TargetMoverComponent>());
	m_targets = dae::SceneManager::GetInstance().GetActiveScene().FindObjectsWithComponent<HealthComponent>();
	GetGameObject()->GetComponent<TargetMoverComponent>()->SetTargetObj(m_targets[0]);
}

pacman::GhostComponent::~GhostComponent()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

int pacman::GhostComponent::GetDamage() const
{
	return m_damage;
}

pacman::MovementBase* pacman::GhostComponent::GetMoveStrategy()
{
	return m_moveStrategy.get();
}

void pacman::GhostComponent::Update(float elapsedSec)
{
	auto newState{ m_ghostState->Update(*this, elapsedSec) };
	if (newState != nullptr)
	{
		m_ghostState->OnExit(*this);
		m_ghostState = std::move(newState);
		m_ghostState->OnEnter(*this);
	}
}

void pacman::GhostComponent::Notify(dae::GameObject* sender, const dae::Event& event)
{
	if (event.id == "PLAYER_DIED")
	{
		// Find new target
		RemoveTarget(sender);
		if (m_targets.size() > 0)
		{
			GetGameObject()->GetComponent<pacman::TargetMoverComponent>()->SetTargetObj(m_targets[0]);
		}
	}
	

	auto newState{ m_ghostState->Notify(*this, sender, event)};
	if (newState != nullptr)
	{
		m_ghostState->OnExit(*this);
		m_ghostState = std::move(newState);
		m_ghostState->OnEnter(*this);
	}
}

void pacman::GhostComponent::RemoveTarget(dae::GameObject* target)
{
	std::erase_if(m_targets, [&](dae::GameObject* t)
		{
			return t == target;
		});
}
