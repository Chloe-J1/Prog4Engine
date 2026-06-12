#include "CountdownComponent.h"
#include "../Minigin/EventQueue.h"
#include "../Minigin/RenderComponent.h"

pacman::CountdownComponent::CountdownComponent(dae::GameObject* owner):
	Component(owner)
{
}

void pacman::CountdownComponent::Update(float elapsedSec)
{
	m_timer += elapsedSec;
	if (m_timer >= m_maxTime)
	{
		dae::EventQueue::GetInstance().Invoke(dae::Event{ "START" });
		GetGameObject()->GetComponent<dae::RenderComponent>()->SetIsEnabled(false);
		this->SetIsEnabled(false);
	}
}