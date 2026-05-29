#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/Subject.h"
#include "../Minigin/EventQueue.h"
#include <memory>
#include <string>
#include "../Minigin/SpriteComponent.h"
namespace pacman
{
	class GameObject;
	class ButtonComponent : public dae::Component
	{
	public:
		ButtonComponent(dae::GameObject* owner);
		~ButtonComponent();
		ButtonComponent(const ButtonComponent& other) = delete;
		ButtonComponent(ButtonComponent&& other) = delete;
		ButtonComponent& operator=(const ButtonComponent& other) = delete;
		ButtonComponent& operator=(ButtonComponent&& other) = delete;

		void SetIsSelected(bool isSelected);
		void ButtonPressed();
	private:
		bool m_isSelected;
		dae::EventQueue* m_eventQueue;
		dae::SpriteComponent* m_spriteComp{};
	};
}