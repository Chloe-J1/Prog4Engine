#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/IEventHandler.h"
#include <array>
namespace dae
{
	class TextComponent;
}
namespace pacman
{
	class LetterSelectComponent final : public dae::Component, public dae::IEventHandler
	{
	public:
		LetterSelectComponent(dae::GameObject* owner, dae::GameObject* upButton, dae::GameObject* downButton);
		~LetterSelectComponent();
		LetterSelectComponent(const LetterSelectComponent& other) = delete;
		LetterSelectComponent(LetterSelectComponent&& other) = delete;
		LetterSelectComponent& operator=(const LetterSelectComponent& other) = delete;
		LetterSelectComponent& operator=(LetterSelectComponent&& other) = delete;

		virtual void Start() override;
		void Notify(const dae::Event& event);
		char GetLetter() const;
	private:
		dae::TextComponent* m_textComp{};
		dae::GameObject* m_upButton;
		dae::GameObject* m_downButton;
		static const std::array<char, 26> m_possibleLetters;
		int m_selectedLetterIdx{ 0 };
	};
}