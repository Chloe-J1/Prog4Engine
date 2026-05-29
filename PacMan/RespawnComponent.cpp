#include "RespawnComponent.h"
#include "../Minigin/EventQueue.h"

pacman::RespawnComponent::RespawnComponent(dae::GameObject* owner, const glm::vec2& respawnPos) :
	Component(owner),
	m_respawnPos{respawnPos}
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

pacman::RespawnComponent::~RespawnComponent()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::RespawnComponent::Notify(dae::GameObject*, const dae::Event& event)
{
	if (event.id == "PLAYER_TAKES_DAMAGE")
	{
		GetGameObject()->SetLocalPosition(m_respawnPos);
	}
}
