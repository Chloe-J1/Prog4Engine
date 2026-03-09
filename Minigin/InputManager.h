#pragma once
#include "Singleton.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include "Commands.h"
#include <map>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Cleanup();

		bool ProcessInput();
		bool IsDownThisFrame(unsigned int button) const;
		bool IsReleasedThisFrame(unsigned int button) const;

		void BindCommand(unsigned int button, std::unique_ptr<Command> command);
		void UnbindCommand(unsigned int button);

	private:
		int m_controllerIndex{ 0 }; // up to 4
		XINPUT_STATE m_currentState{};
		XINPUT_STATE m_previousState{};
		WORD m_buttonsPressedThisFrame{};
		WORD m_buttonsReleasedThisFrame{};

		std::map<unsigned int, std::unique_ptr<Command>> m_buttonsMap;
	};

}
