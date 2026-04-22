#include "ButtonComponent.h"
#include "MenuManager.h"
#include "GamestateManager.h"
#include "Events.h"
#include "../Minigin/Event.h"


pacman::ButtonComponent::ButtonComponent(dae::GameObject* owner, const std::string& name):
	Component(owner),
	m_isSelected{false},
	m_name{name}
{
	m_eventQueue = &dae::EventQueue::GetInstance();
	m_spriteComp = GetGameObject()->GetComponent<dae::SpriteComponent>();
	if (m_spriteComp == nullptr)
		std::cout << "no spritecomp\n";
	MenuManager::GetInstance().RegisterButton(this);
}

pacman::ButtonComponent::~ButtonComponent()
{
	MenuManager::GetInstance().UnregisterButton(this);
}

void pacman::ButtonComponent::SetIsSelected(bool isSelected)
{
	m_isSelected = isSelected;
	
	if (isSelected)
		m_spriteComp->SetRow(1);
	else
		m_spriteComp->SetRow(0);
}

void pacman::ButtonComponent::ButtonPressed()
{
	if (m_isSelected)
	{
		dae::Event buttonPressed{"BUTTON_PRESSED"};
		m_eventQueue->Invoke(std::move(buttonPressed), GetGameObject());
	}
}

const std::string& pacman::ButtonComponent::GetName() const
{
	return m_name;
}
