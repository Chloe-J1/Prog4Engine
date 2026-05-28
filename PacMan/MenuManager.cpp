#include "MenuManager.h"

void pacman::MenuManager::SelectNextButton()
{
	// Deselect old button
	m_buttons[m_currButtonIdx]->SetIsSelected(false);

	// Select next button
	++m_currButtonIdx;
	if (m_currButtonIdx > (int)m_buttons.size() - 1)
		m_currButtonIdx = 0;

	m_buttons[m_currButtonIdx]->SetIsSelected(true);
}

void pacman::MenuManager::SelectPreviousButton()
{
	// Deselect old button
	m_buttons[m_currButtonIdx]->SetIsSelected(false);

	// Select previous button
	--m_currButtonIdx;
	if (m_currButtonIdx < 0)
		m_currButtonIdx = (int)m_buttons.size() - 1;

	m_buttons[m_currButtonIdx]->SetIsSelected(true);
}

void pacman::MenuManager::RegisterButton(ButtonComponent* button)
{
	m_buttons.push_back(button);

	// Make the first button the current selected button
	if (m_buttons.size() == 1)
		m_buttons[0]->SetIsSelected(true);
}

void pacman::MenuManager::UnregisterButton(ButtonComponent* button)
{
	if (m_buttons.empty()) return; // Prevent cleanup when singleton already doesn't exist anymore
	std::erase_if(m_buttons, [&](ButtonComponent* b) { return button == b; });
}

void pacman::MenuManager::ResetSelected()
{
	m_currButtonIdx = 0;
}
