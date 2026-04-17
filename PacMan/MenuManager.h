#pragma once
#include "../Minigin/Singleton.h"
#include <vector>
#include "ButtonComponent.h"

#include <iostream>
namespace pacman
{
	class MenuManager final : public dae::Singleton<MenuManager>
	{
	public:

		~MenuManager()
		{
			m_buttons.clear();
		}

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
		}

		void UnregisterButton(ButtonComponent* button)
		{
			if (m_buttons.empty()) return; // Prevent cleanup when singleton already doesn't exist anymore
			std::erase_if(m_buttons, [&](ButtonComponent* b) { return button == b; });
		}
	private:
		std::vector<ButtonComponent*> m_buttons;
		int m_currButtonIdx{ 0 };
	};
}