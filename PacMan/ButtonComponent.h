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
		ButtonComponent(dae::GameObject* owner, const std::string& name);
		~ButtonComponent();
		ButtonComponent(const ButtonComponent& other) = delete;
		ButtonComponent(ButtonComponent&& other) = delete;
		ButtonComponent& operator=(const ButtonComponent& other) = delete;
		ButtonComponent& operator=(ButtonComponent&& other) = delete;

		void SetIsSelected(bool isSelected);
		void ButtonPressed();
		const std::string& GetName() const;
	private:
		bool m_isSelected;
		std::string m_name;
		dae::EventQueue* m_eventQueue;
		dae::SpriteComponent* m_spriteComp{};
	};
}