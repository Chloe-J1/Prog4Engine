#include "ButtonComponent.h"
#include "MenuManager.h"
#include "../Minigin/Event.h"
#include "Events.h"
#include <memory>
#include <iostream>
#include "Commands.h"


pacman::ButtonComponent::ButtonComponent(dae::GameObject* owner):
	Component(owner),
	m_isSelected{false}
{
	m_eventQueue = &dae::EventQueue::GetInstance();
	m_spriteComp = GetGameObject()->GetComponent<dae::SpriteComponent>();
	if (m_spriteComp == nullptr)
		std::cout << "no spritecomp\n";
	MenuManager::GetInstance().RegisterButton(this);

	m_inputManager.BindCommand(SDL_SCANCODE_SPACE, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PressButton>(owner));
	m_inputManager.BindCommand(dae::Input::Button_A, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PressButton>(owner), 0);
	m_inputManager.BindCommand(dae::Input::Button_A, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PressButton>(owner), 1);
}

pacman::ButtonComponent::~ButtonComponent()
{
	MenuManager::GetInstance().UnregisterButton(this);
	m_inputManager.UnbindCommand(SDL_SCANCODE_SPACE, dae::TriggerEvent::PressedThisFrame);
	m_inputManager.UnbindCommand(dae::Input::Button_A, dae::TriggerEvent::PressedThisFrame, 0);
	m_inputManager.UnbindCommand(dae::Input::Button_A, dae::TriggerEvent::PressedThisFrame, 1);
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