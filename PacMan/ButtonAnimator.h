#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/Observer.h"
#include "../Minigin/EventQueue.h"
#include "Events.h"

#include <iostream>
namespace pacman
{
	class ButtonAnimator final : public dae::Component, public dae::Observer
	{
	public:
		ButtonAnimator(dae::GameObject* owner):
			Component(owner)
		{
			dae::EventQueue::GetInstance().AddObserver(this);
		}
		~ButtonAnimator()
		{
			dae::EventQueue::GetInstance().RemoveObserver(this);
		}
		ButtonAnimator(const ButtonAnimator& other) = delete;
		ButtonAnimator(ButtonAnimator&& other) = delete;
		ButtonAnimator& operator=(const ButtonAnimator& other) = delete;
		ButtonAnimator& operator=(ButtonAnimator&& other) = delete;

		virtual void Notify(dae::GameObject* gameObject, const dae::Event& event) override
		{
			if (event.id == "BUTTON_SELECTION_CHANGED")
			{
				auto* arg = static_cast<ButtonSelectionArg*>(event.arg.get());
				m_isSelected = arg->isSelected;
				
				dae::SpriteComponent* spriteComp{ gameObject->GetComponent<dae::SpriteComponent>() };
				UpdateSelected(spriteComp);
			}
		}
	private:
		bool m_isSelected{ false };

		void UpdateSelected(dae::SpriteComponent* spriteComp)
		{
			if (m_isSelected)
			{
				spriteComp->SetRow(1);
			}
			else
			{
				spriteComp->SetRow(0);
			}
		}
	};
}