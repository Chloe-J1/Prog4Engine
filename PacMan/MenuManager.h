#pragma once
#include "../Minigin/Singleton.h"
#include "../Minigin/EventQueue.h"
#include "../Minigin/Observer.h"
#include <vector>
#include "ButtonComponent.h"
#include "GamestateManager.h"

#include <iostream>
namespace pacman
{
	class MenuManager final : public dae::Singleton<MenuManager>, public dae::Observer
	{
	public:
		MenuManager()
		{
			dae::EventQueue::GetInstance().AddObserver(this);
		}
		~MenuManager()
		{
			dae::EventQueue::GetInstance().RemoveObserver(this);
		}
		MenuManager(const MenuManager& other) = delete;
		MenuManager(MenuManager&& other) = delete;
		MenuManager& operator=(const MenuManager& other) = delete;
		MenuManager& operator=(MenuManager&& other) = delete;

		void SelectNextButton()
		{
			// Deselect old button
			m_buttons[m_currButtonIdx]->SetIsSelected(false);

			// Select next button
			++m_currButtonIdx;
			if (m_currButtonIdx > (int)m_buttons.size() - 1)
				m_currButtonIdx = 0;

			m_buttons[m_currButtonIdx]->SetIsSelected(true);
		}

		void SelectPreviousButton()
		{
			// Deselect old button
			m_buttons[m_currButtonIdx]->SetIsSelected(false);

			// Select previous button
			--m_currButtonIdx;
			if (m_currButtonIdx < 0)
				m_currButtonIdx = (int)m_buttons.size() - 1;

			m_buttons[m_currButtonIdx]->SetIsSelected(true);
		}

		void RegisterButton(ButtonComponent* button)
		{
			m_buttons.push_back(button);

			// Make the first button the current selected button
			if (m_buttons.size() == 1)
				m_buttons[0]->SetIsSelected(true);
		}

		void UnregisterButton(ButtonComponent* button)
		{
			if (m_buttons.empty()) return; // Prevent cleanup when singleton already doesn't exist anymore
			std::erase_if(m_buttons, [&](ButtonComponent* b) { return button == b; });
		}

		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override
		{
			if (event.id == "BUTTON_PRESSED")
			{
				ButtonComponent* button{ sender->GetComponent<ButtonComponent>() };

				if (button->GetName() == "LoadGameScene")
				{
					GamestateManager::GetInstance().GameScene();
				}
				else if (button->GetName() == "LoadLoseScene")
				{
					GamestateManager::GetInstance().MapScene();
				}
			}
		}
	private:
		std::vector<ButtonComponent*> m_buttons;
		int m_currButtonIdx{ 0 };
	};
}