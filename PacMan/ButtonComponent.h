#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/EventQueue.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/InputManager.h"

namespace pacman
{
	class GameObject;
	class ButtonComponent final : public dae::Component
	{
	public:
		explicit ButtonComponent(dae::GameObject* owner);
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
		dae::InputManager& m_inputManager{ dae::InputManager::GetInstance() };
	};
}