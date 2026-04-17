#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/Observer.h"
#include "Events.h"
namespace pacman
{
	class ButtonAnimator final : public dae::Component, public dae::Observer
	{
	public:
		ButtonAnimator(dae::GameObject* owner, dae::SpriteComponent* spriteComp):
			Component(owner),
			m_spriteComp{spriteComp}
		{
			UpdateSelected();
		}

		virtual void Notify(dae::GameObject*, const dae::Event& event) override
		{
			if (event.id == "BUTTON_SELECITON_CHANGED")
			{
				auto* arg = static_cast<ButtonSelectionArg*>(event.arg.get());
				m_isSelected = arg->isSelected;
				
				UpdateSelected();
			}
		}
	private:
		dae::SpriteComponent* m_spriteComp;
		bool m_isSelected{ false };

		void UpdateSelected()
		{
			if (m_isSelected)
			{
				m_spriteComp->SetRow(1);
			}
			else
			{
				m_spriteComp->SetRow(0);
			}
		}
	};
}