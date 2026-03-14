#include "Controller.h"

#if WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>

#include <iostream>



class dae::Controller::ControllerImpl
{
public:
    ControllerImpl(int index): 
		m_controllerIndex(index) 
	{}

	void ProcessInput()
	{

		CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
		XInputGetState(m_controllerIndex, &m_currentState);

		auto buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
		m_buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
		m_buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);
		
		std::cout << m_currentState.Gamepad.wButtons << "\n";
	}

	bool IsDownThisFrame(Controller::Input button) const
	{
		return m_buttonsPressedThisFrame & (unsigned int)button;
	}

	bool IsReleasedThisFrame(Controller::Input button) const
	{
		return m_buttonsReleasedThisFrame & (unsigned int)button;
	}

	bool IsHold(Controller::Input button) const
	{
		return m_currentState.Gamepad.wButtons & (unsigned int)button;
	}

	glm::vec2 GetRightStickValues() const
	{
		return glm::vec2(m_currentState.Gamepad.sThumbRX, m_currentState.Gamepad.sThumbRY);
	}

	glm::vec2 GetLeftStickValues() const
	{
		return glm::vec2(m_currentState.Gamepad.sThumbLX, m_currentState.Gamepad.sThumbLY);
	}
private:
    int m_controllerIndex{ 0 };
    XINPUT_STATE m_currentState{};
    XINPUT_STATE m_previousState{};
    WORD m_buttonsPressedThisFrame{};
    WORD m_buttonsReleasedThisFrame{};
};

#else
class dae::Controller::ControllerImpl
{
public:
	ControllerImpl(int){}
	void ProcessInput() {}
	bool IsDownThisFrame(Controller::Input) const { return false; }
	bool IsReleasedThisFrame(Controller::Input) const { return false; }
	bool IsHold(Controller::Input) const { return false; }
	glm::vec2 GetLeftStickValues() const { return {}; }
	glm::vec2 GetRightStickValues() const { return {}; }
};

#endif

namespace dae
{
    Controller::Controller(int index): 
        m_pImpl(std::make_unique<ControllerImpl>(index))
    {}
    Controller::~Controller() = default;

	void Controller::ProcessInput() 
	{ 
		m_pImpl->ProcessInput(); 
	}
	bool Controller::IsDownThisFrame(Controller::Input b) const 
	{ 
		return m_pImpl->IsDownThisFrame(Controller::Input(b));
	}
	bool Controller::IsReleasedThisFrame(Controller::Input b) const
	{ 
		return m_pImpl->IsReleasedThisFrame(Controller::Input(b));
	}
	bool Controller::IsHold(Controller::Input b) const
	{
		return m_pImpl->IsHold(Controller::Input(b));
	}
	glm::vec2 Controller::GetLeftStickValues() const 
	{ 
		return m_pImpl->GetLeftStickValues(); 
	}
	glm::vec2 Controller::GetRightStickValues() const 
	{ 
		return m_pImpl->GetRightStickValues(); 
	}
}