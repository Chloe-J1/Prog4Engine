#include "GhostComponent.h"
#include "GhostState.h"
#include "../Minigin/EventQueue.h"
#include "TargetMoverComponent.h"
#include "../Minigin/SceneManager.h"
#include "HealthComponent.h"
#include <utility>
#include "Events.h"
#include "PlayerMovement.h"

pacman::GhostComponent::GhostComponent(dae::GameObject* owner, std::unique_ptr<MovementBase> moveStrategy):
	Component(owner),
	m_damage{ 1 },
	m_ghostState{std::make_unique<NotReadyState>()},
	m_moveStrategy{std::move(moveStrategy)}
{
	if (auto* strategy = dynamic_cast<NonAIMovement*>(m_moveStrategy.get()))
	{
		strategy->Init(GetGameObject()->GetComponent<PlayerMovement>());
	}
	m_ghostState->OnEnter(*this);
	dae::EventQueue::GetInstance().AddEventHandler(this);
	m_moveStrategy->Init(GetGameObject()->GetComponent<TargetMoverComponent>());
}

void pacman::GhostComponent::Start()
{
	m_targets = dae::SceneManager::GetInstance().GetActiveScene().FindObjectsWithComponent<HealthComponent>();
	GetGameObject()->GetComponent<TargetMoverComponent>()->SetTargetObj(m_targets[rand() % m_targets.size()]);
}

pacman::GhostComponent::~GhostComponent()
{
	dae::EventQueue::GetInstance().RemoveEventHandler(this);
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

void pacman::GhostComponent::Notify(const dae::Event& event)
{
	if (event.id == "PLAYER_DIED")
	{
		// Find new target
		auto* arg = static_cast<SenderArg*>(event.arg.get());
		RemoveTarget(arg->sender);
		if (m_targets.size() > 0)
		{
			int rndIndex{ int(rand() % m_targets.size()) };
			GetGameObject()->GetComponent<pacman::TargetMoverComponent>()->SetTargetObj(m_targets[rndIndex]);
		}
	}

	auto newState{ m_ghostState->Notify(*this, event)};
	if (newState != nullptr)
	{
		m_ghostState->OnExit(*this);
		m_ghostState = std::move(newState);
		m_ghostState->OnEnter(*this);
	}
}

void pacman::GhostComponent::OnCollision(dae::GameObject* other)
{
	auto newState{ m_ghostState->OnCollision(*this, other) };
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