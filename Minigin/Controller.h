#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
namespace dae
{
	class Controller
	{
	public:
		Controller(int index);

		void ProcessInput();

		bool IsDownThisFrame(unsigned int button) const;
		bool IsReleasedThisFrame(unsigned int button) const;
		bool IsHold(unsigned int button) const;
	private:

		int m_controllerIndex{ 0 }; // up to 4
		XINPUT_STATE m_currentState{};
		XINPUT_STATE m_previousState{};
		WORD m_buttonsPressedThisFrame{};
		WORD m_buttonsReleasedThisFrame{};
	};
}


