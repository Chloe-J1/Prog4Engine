#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <glm/vec2.hpp>
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
		glm::vec2 GetRightStickValues() const;
		glm::vec2 GetLeftStickValues() const;
	private:

		int m_controllerIndex{ 0 }; 
		XINPUT_STATE m_currentState{};
		XINPUT_STATE m_previousState{};
		WORD m_buttonsPressedThisFrame{};
		WORD m_buttonsReleasedThisFrame{};
	};
}


