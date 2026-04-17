#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/Subject.h"
#include <memory>
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

		dae::Subject* GetSubject();
	private:
		bool m_isSelected;
		std::unique_ptr<dae::Subject> m_subject;
	};
}