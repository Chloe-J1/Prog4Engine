#include "ButtonComponent.h"
#include "MenuManager.h"

#include "GamestateManager.h"
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

void pacman::ButtonComponent::ButtonPressed()
{
	if(m_isSelected)
		GamestateManager::GetInstance().GameScene(); // TODO: make it load the corresponding scene
}
