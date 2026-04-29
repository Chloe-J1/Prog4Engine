#include "Controller.h"

#if WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <algorithm>

#include <iostream>


class dae::Controller::ControllerImpl
{
public:
	//XInput	
 
 
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
	}

	bool IsDownThisFrame(Input button) const
	{
		return m_buttonsPressedThisFrame & (unsigned int)button;
	}

	bool IsReleasedThisFrame(Input button) const
	{
		return m_buttonsReleasedThisFrame & (unsigned int)button;
	}

	bool IsHold(Input button) const
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
	// Emscripten
#else
#include <SDL3/SDL.h>
#include <iostream>
class dae::Controller::ControllerImpl
{
	
public:
	ControllerImpl(int index):
		m_controllerIndex{index}
	{
		int count = 0;
		SDL_JoystickID* ids = SDL_GetGamepads(&count);

		m_gamepad = SDL_OpenGamepad(ids[m_controllerIndex]);
		SDL_free(ids);
	}

	void ProcessInput() 
	{
		memcpy(m_previousState, m_currentState, sizeof(m_currentState));

		for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; i++)
			m_currentState[i] = SDL_GetGamepadButton(m_gamepad, (SDL_GamepadButton)i);
	}
	bool IsDownThisFrame(Input button) const
	{ 
		return m_currentState[(SDL_GamepadButton)button] && !m_previousState[(SDL_GamepadButton)button];
	}
	bool IsReleasedThisFrame(Input button) const 
	{
		return !m_currentState[(SDL_GamepadButton)button] && m_previousState[(SDL_GamepadButton)button];
	}
	bool IsHold(Input button) const
	{
		return m_currentState[(SDL_GamepadButton)button];
	}
	glm::vec2 GetLeftStickValues() const 
	{  
		return glm::vec2{ SDL_GetGamepadAxis(m_gamepad, SDL_GAMEPAD_AXIS_LEFTX) / (float)SDL_JOYSTICK_AXIS_MAX, SDL_GetGamepadAxis(m_gamepad, SDL_GAMEPAD_AXIS_LEFTY) / (float)SDL_JOYSTICK_AXIS_MAX };
	}
	glm::vec2 GetRightStickValues() const 
	{
		return glm::vec2{ SDL_GetGamepadAxis(m_gamepad, SDL_GAMEPAD_AXIS_RIGHTX) / (float)SDL_JOYSTICK_AXIS_MAX, SDL_GetGamepadAxis(m_gamepad, SDL_GAMEPAD_AXIS_RIGHTY) / (float)SDL_JOYSTICK_AXIS_MAX };
	}


private:
	int m_controllerIndex;
	bool m_previousState[SDL_GAMEPAD_BUTTON_COUNT] = {};
	bool m_currentState[SDL_GAMEPAD_BUTTON_COUNT] = {};
	SDL_Gamepad* m_gamepad{};
};

#endif
	// Shared
namespace dae
{
    Controller::Controller(int index): 
        m_impl(std::make_unique<ControllerImpl>(index))
    {}
    Controller::~Controller() = default;

	void Controller::ProcessInput()
	{
		m_impl->ProcessInput();

		for (auto& commands : m_controllerBindings)
		{
			switch (commands.triggerEvent)
			{
			case dae::TriggerEvent::Hold:
				if (IsHold(commands.ctrlInput))
					commands.command->Execute();
				break;
			case dae::TriggerEvent::PressedThisFrame:
				if (IsDownThisFrame(commands.ctrlInput))
					commands.command->Execute();
				break;
			case dae::TriggerEvent::ReleasedThisFrame:
				if (IsReleasedThisFrame(commands.ctrlInput))
					commands.command->Execute();
				break;
			}
		}
	}
	void Controller::BindCommand(Input button, TriggerEvent triggerEvent, std::unique_ptr<Command> command)
	{
		m_controllerBindings.emplace_back(Bindings(button, triggerEvent, std::move(command)));
	}
	void Controller::UnbindCommand(Input button, TriggerEvent triggerEvent)
	{
		auto itr = std::find_if(m_controllerBindings.begin(), m_controllerBindings.end(), [=](const Bindings& bindings) {return bindings.ctrlInput == button && bindings.triggerEvent == triggerEvent; });
		if (itr == m_controllerBindings.end()) return; // no such bindings found
		m_controllerBindings.erase(itr);
	}
	void Controller::UnbindAllCommands()
	{
		m_controllerBindings.clear();
	}
	bool Controller::IsDownThisFrame(Input button) const 
	{ 
		return m_impl->IsDownThisFrame(Input(button));
	}
	bool Controller::IsReleasedThisFrame(Input button) const
	{ 
		return m_impl->IsReleasedThisFrame(Input(button));
	}
	bool Controller::IsHold(Input button) const
	{
		return m_impl->IsHold(Input(button));
	}
	glm::vec2 Controller::GetLeftStickValues() const 
	{ 
		return m_impl->GetLeftStickValues(); 
	}
	glm::vec2 Controller::GetRightStickValues() const 
	{ 
		return m_impl->GetRightStickValues(); 
	}
}