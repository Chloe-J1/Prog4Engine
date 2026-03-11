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
		enum class Input
		{
			DPad_Up = 1,
			DPad_Down = 2,
			DPad_Left = 4,
			DPad_Right = 8
		};

		Controller(int index);

		void ProcessInput();

		bool IsDownThisFrame(Input button) const;
		bool IsReleasedThisFrame(Input button) const;
		bool IsHold(Input button) const;
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


