#pragma once
#include "Component.h"
#include "IEventHandler.h"
#include "TextComponent.h"


namespace pacman
{
	class ScoreComponentUI final : public dae::Component, public dae::IEventHandler
	{
	public:
		explicit ScoreComponentUI(dae::GameObject* owner, dae::GameObject* pacman);
		~ScoreComponentUI();
		ScoreComponentUI(const ScoreComponentUI& other) = delete;
		ScoreComponentUI(ScoreComponentUI&& other) = delete;
		ScoreComponentUI& operator=(const ScoreComponentUI& other) = delete;
		ScoreComponentUI& operator=(ScoreComponentUI&& other) = delete;


		void Notify(const dae::Event& event);
		

	private:
		dae::TextComponent* m_textComponent;
		dae::GameObject* m_pacman;
	};
}