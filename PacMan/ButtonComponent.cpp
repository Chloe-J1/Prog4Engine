#include "ButtonComponent.h"
#include "MenuManager.h"


#include "GamestateManager.h"
pacman::ButtonComponent::ButtonComponent(dae::GameObject* owner):
	Component(owner),
	m_isSelected{false},
	m_subject{std::make_unique<dae::Subject>()}
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
	// Notify observers
	dae::Event selectionChangedEvent{ "BUTTON_SELECITON_CHANGED" };
	selectionChangedEvent.arg = std::make_unique<ButtonSelectionArg>(isSelected);
	m_subject->NotifyObservers(GetGameObject(), std::move(selectionChangedEvent));
}

void pacman::ButtonComponent::ButtonPressed()
{
	if(m_isSelected)
		GamestateManager::GetInstance().GameScene(); // TODO: make it load the corresponding scene
}

dae::Subject* pacman::ButtonComponent::GetSubject()
{
	return m_subject.get();
}
