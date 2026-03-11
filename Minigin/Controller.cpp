#include "Controller.h"
dae::Controller::Controller(int index):
	m_controllerIndex{index}
{
}

void dae::Controller::ProcessInput()
{
	
	CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
	XInputGetState(m_controllerIndex, &m_currentState);

	auto buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
	m_buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
	m_buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);

	
}

bool dae::Controller::IsDownThisFrame(Input button) const
{
	return m_buttonsPressedThisFrame & (unsigned int)button;
}

bool dae::Controller::IsReleasedThisFrame(Input button) const
{
	return m_buttonsReleasedThisFrame & (unsigned int)button;
}

bool dae::Controller::IsHold(Input button) const
{
	return m_currentState.Gamepad.wButtons & (unsigned int)button;
}

glm::vec2 dae::Controller::GetRightStickValues() const
{
	return glm::vec2(m_currentState.Gamepad.sThumbRX, m_currentState.Gamepad.sThumbRY);
}

glm::vec2 dae::Controller::GetLeftStickValues() const
{
	return glm::vec2(m_currentState.Gamepad.sThumbLX, m_currentState.Gamepad.sThumbLY);
}
