#pragma once
#include "Singleton.h"

#include "Commands.h"
#include <map>
#include <memory>
#include <vector>
#include "Controller.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:

		bool ProcessInput();

		void BindCommand(Controller::Input button, std::unique_ptr<Command> command);
		void UnbindCommand(Controller::Input button);
		void BindCommand(SDL_Scancode button, std::unique_ptr<Command> command);
		void UnbindCommand(SDL_Scancode button);

		void AddController();
	private:
		
		bool IsDownThisFrame(SDL_Scancode button) const;
		bool IsReleasedThisFrame(SDL_Scancode button) const;
		bool IsHold(SDL_Scancode button) const;


		const bool* m_keyboardState{ nullptr };
		bool m_previousKeyboardState[SDL_SCANCODE_COUNT]{};

		std::map<SDL_Scancode, std::unique_ptr<Command>> m_keyboardMap;
		std::map<Controller::Input, std::unique_ptr<Command>> m_controllerMap;
		std::vector<Controller> m_controllers;

		int m_nrCtrlrs{ 0 };
		const int m_maxCtrlrs{ 4 };
	};

}
