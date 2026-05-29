#include "EatenComponent.h"
#include "../Minigin/EventQueue.h"
#include  "HealthComponent.h"
#include "Events.h"

pacman::EatenComponent::EatenComponent(dae::GameObject* owner):
	Component(owner)
{
	m_eventQueue = &dae::EventQueue::GetInstance();
}

void pacman::EatenComponent::SetVulnerable(bool isVulnerable)
{
	m_isVulnerable = isVulnerable;
}

void pacman::EatenComponent::OnCollision(dae::GameObject* other)
{
	if (auto player = other->GetComponent<HealthComponent>())
	{
		if (m_isVulnerable)
		{
			dae::Event deathEvent{"GHOST_DIED"};
			std::unique_ptr<GhostDiedArg> arg = std::make_unique<GhostDiedArg>(GetGameObject());
			deathEvent.arg = std::move(arg);
			m_eventQueue->Invoke(std::move(deathEvent), GetGameObject());
		}
	}
}
