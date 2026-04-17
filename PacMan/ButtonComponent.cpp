#include "ButtonComponent.h"
#include "MenuManager.h"
pacman::ButtonComponent::ButtonComponent(dae::GameObject* owner):
	Component(owner),
	m_isSelected{false}
{
	MenuManager::GetInstance().RegisterButton(this);
}

pacman::ButtonComponent::~ButtonComponent()
{
	MenuManager::GetInstance().UnregisterButton(this);
}

void pacman::ButtonComponent::SetIsSelected(bool isSelected)
{
	m_isSelected = isSelected;
}
