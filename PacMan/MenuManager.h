#pragma once
#include "../Minigin/Singleton.h"
#include <vector>
#include "ButtonComponent.h"

namespace pacman
{
	class MenuManager final : public dae::Singleton<MenuManager>
	{
	public:

		void SelectNextButton();

		void SelectPreviousButton();

		void RegisterButton(ButtonComponent* button);

		void UnregisterButton(ButtonComponent* button);
	private:
		std::vector<ButtonComponent*> m_buttons;
		int m_currButtonIdx{ 0 };
	};
}