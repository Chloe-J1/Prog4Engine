#pragma once
#include "Component.h"
#include "Observer.h"
#include "TextComponent.h"


namespace pacman
{
	class ScoreComponentUI : public dae::Component, public dae::Observer
	{
	public:
		ScoreComponentUI(dae::GameObject* owner);

		virtual void Notify(dae::GameObject*, const dae::Event& event) override;
		

	private:
		dae::TextComponent* m_textComponent;
	};
}