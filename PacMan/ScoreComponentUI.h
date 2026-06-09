#pragma once
#include "Component.h"
#include "IObserver.h"
#include "TextComponent.h"


namespace pacman
{
	class ScoreComponentUI : public dae::Component, public dae::IObserver
	{
	public:
		ScoreComponentUI(dae::GameObject* owner, dae::GameObject* pacman);
		~ScoreComponentUI();
		ScoreComponentUI(const ScoreComponentUI& other) = delete;
		ScoreComponentUI(ScoreComponentUI&& other) = delete;
		ScoreComponentUI& operator=(const ScoreComponentUI& other) = delete;
		ScoreComponentUI& operator=(ScoreComponentUI&& other) = delete;


		virtual void Notify(dae::GameObject*, const dae::Event& event) override;
		

	private:
		dae::TextComponent* m_textComponent;
		dae::GameObject* m_pacman;
	};
}