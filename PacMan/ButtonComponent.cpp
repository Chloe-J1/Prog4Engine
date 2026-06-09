#include "ButtonComponent.h"
#include "MenuManager.h"
#include "../Minigin/Event.h"
#include "Events.h"
#include <memory>
#include <iostream>


pacman::ButtonComponent::ButtonComponent(dae::GameObject* owner):
	Component(owner),
	m_isSelected{false}
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
		buttonPressed.arg = std::make_unique<pacman::SenderArg>(GetGameObject());
		m_eventQueue->Invoke(std::move(buttonPressed));
	}
}