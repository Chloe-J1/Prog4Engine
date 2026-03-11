#include <SDL3/SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl3.h"


#include <iostream>



bool dae::InputManager::ProcessInput()
{
	// XINPUT -> controller
	//********
	for (auto& controller : m_controllers)
	{
		controller.ProcessInput();
		for (const auto& commands : m_controllerMap)
		{
			switch (commands.second->GetEventType())
			{
			case dae::TriggerEvent::Hold:
				if (controller.IsHold(commands.first))
					commands.second->Execute();
				break;
			case dae::TriggerEvent::PressedThisFrame:
				if (controller.IsDownThisFrame(commands.first))
					commands.second->Execute();
				break;
			case dae::TriggerEvent::ReleasedThisFrame:
				if (controller.IsReleasedThisFrame(commands.first))
					commands.second->Execute();
				break;
			}
		}
	}
	
	std::cout << m_controllers[0].GetLeftStickValues().x << "       " << m_controllers[0].GetLeftStickValues().y << "\n";

	// SDL -> keyboard
	//********
	if(m_keyboardState == nullptr)
		m_keyboardState = SDL_GetKeyboardState(nullptr);

	memcpy(m_previousKeyboardState, m_keyboardState, SDL_SCANCODE_COUNT);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}

		//process event for IMGUI
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	m_keyboardState = SDL_GetKeyboardState(nullptr);
	

	for (const auto& commands : m_keyboardMap)
	{
		switch (commands.second->GetEventType())
		{
		case dae::TriggerEvent::Hold:
			if (IsHold(commands.first))
				commands.second->Execute();
			break;
		case dae::TriggerEvent::PressedThisFrame:
			if (IsDownThisFrame(commands.first))
				commands.second->Execute();
			break;
		case dae::TriggerEvent::ReleasedThisFrame:
			if (IsReleasedThisFrame(commands.first))
				commands.second->Execute();
			break;
		}
	}

	
	return true;
}



bool dae::InputManager::IsDownThisFrame(SDL_Scancode button) const
{
	return m_keyboardState[button] && !m_previousKeyboardState[button];
}

bool dae::InputManager::IsReleasedThisFrame(SDL_Scancode button) const
{
	return !m_keyboardState[button] && m_previousKeyboardState[button];
}

bool dae::InputManager::IsHold(SDL_Scancode button) const
{
	return m_keyboardState[button] && m_previousKeyboardState[button];
}

void dae::InputManager::BindCommand(unsigned int button, std::unique_ptr<Command> command)
{
	m_controllerMap[button] = std::move(command);
}

void dae::InputManager::UnbindCommand(unsigned int button)
{
	m_controllerMap.erase(button);
}

void dae::InputManager::BindCommand(SDL_Scancode button, std::unique_ptr<Command> command)
{
	m_keyboardMap[button] = std::move(command);
}

void dae::InputManager::UnbindCommand(SDL_Scancode button)
{
	m_keyboardMap.erase(button);
}

void dae::InputManager::AddController()
{
	if (m_nrCtrlrs < m_maxCtrlrs)
	{
		m_controllers.push_back(Controller(m_nrCtrlrs));
		m_nrCtrlrs++;
	}
}
