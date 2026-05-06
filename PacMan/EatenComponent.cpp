#include "EatenComponent.h"
#include "../Minigin/EventQueue.h"
#include "Events.h"

pacman::EatenComponent::EatenComponent(dae::GameObject* owner):
	Component(owner)
{
	m_eventQueue = &dae::EventQueue::GetInstance();
	m_eventQueue->AddObserver(this);
}

pacman::EatenComponent::~EatenComponent()
{
	m_eventQueue->RemoveObserver(this);
}

void pacman::EatenComponent::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "POWER_PELLET_PICKUP")
	{
		m_isVulnerable = true;
		std::cout << "VULNERABLE\n";
	}
	else if (event.id == "NOT_DIZZIED")
	{
		m_isVulnerable = false;
		std::cout << "NOT VULNERABLE\n";
	}
}

void pacman::EatenComponent::OnCollision(dae::GameObject* other)
{
	if (other->GetLayer() == "Player")
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
