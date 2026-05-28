#include "LetterSelectComponent.h"
#include "../Minigin/TextComponent.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/EventQueue.h"
#include <string>

const std::array<char, 26> pacman::LetterSelectComponent::m_possibleLetters = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

pacman::LetterSelectComponent::LetterSelectComponent(dae::GameObject* owner, dae::GameObject* upButton, dae::GameObject* downButton):
	dae::Component(owner),
	m_upButton{upButton},
	m_downButton{downButton}
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

pacman::LetterSelectComponent::~LetterSelectComponent()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::LetterSelectComponent::Start()
{
	m_textComp = GetGameObject()->GetComponent<dae::TextComponent>();
}

void pacman::LetterSelectComponent::Notify(dae::GameObject* sender, const dae::Event& event)
{
	if (event.id == "BUTTON_PRESSED")
	{
		if (sender == m_downButton)
		{
			if (m_selectedLetterIdx <= 0) return;
			--m_selectedLetterIdx;
			m_textComp->SetText((std::string(1, m_possibleLetters[m_selectedLetterIdx])));
		}
		else if (sender == m_upButton)
		{
			if (m_selectedLetterIdx >= m_possibleLetters.size() - 1) return;
			++m_selectedLetterIdx;
			m_textComp->SetText((std::string(1, m_possibleLetters[m_selectedLetterIdx])));
		}
	}
}

char pacman::LetterSelectComponent::GetLetter() const
{
	return m_possibleLetters[m_selectedLetterIdx];
}
