#include <SDL3/SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl3.h"




dae::InputManager::InputManager()
{
	m_keyboardState = SDL_GetKeyboardState(nullptr);
}

bool dae::InputManager::ProcessInput(float elapsedSec)
{
	// XINPUT -> controller
	//********
	for (auto& controller : m_controllers)
	{
		controller->ProcessInput();
		for (auto& commands : m_controllerMap)
		{
			switch (commands.second.triggerEvent)
			{
			case dae::TriggerEvent::Hold:
				if (controller->IsHold(commands.first))
					commands.second.command->Execute(elapsedSec);
				break;
			case dae::TriggerEvent::PressedThisFrame:
				if (controller->IsDownThisFrame(commands.first))
					commands.second.command ->Execute(elapsedSec);
				break;
			case dae::TriggerEvent::ReleasedThisFrame:
				if (controller->IsReleasedThisFrame(commands.first))
					commands.second.command ->Execute(elapsedSec);
				break;
			}
		}
	}
	

	// SDL -> keyboard
	//********
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
		switch (commands.second.triggerEvent)
		{
		case dae::TriggerEvent::Hold:
			if (IsHold(commands.first))
				commands.second.command->Execute(elapsedSec);
			break;
		case dae::TriggerEvent::PressedThisFrame:
			if (IsDownThisFrame(commands.first))
				commands.second.command->Execute(elapsedSec);
			break;
		case dae::TriggerEvent::ReleasedThisFrame:
			if (IsReleasedThisFrame(commands.first))
				commands.second.command->Execute(elapsedSec);
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

void dae::InputManager::BindCommand(Controller::Input button, TriggerEvent triggerEvent, std::unique_ptr<Command> command)
{
	m_controllerMap[button] = Bindings(triggerEvent, std::move(command));
}

void dae::InputManager::UnbindCommand(Controller::Input button)
{
	m_controllerMap.erase(button);
}

void dae::InputManager::BindCommand(SDL_Scancode button, TriggerEvent triggerEvent, std::unique_ptr<Command> command)
{
	m_keyboardMap[button] = Bindings{ triggerEvent, std::move(command) };
}

void dae::InputManager::UnbindCommand(SDL_Scancode button)
{
	m_keyboardMap.erase(button);
}

void dae::InputManager::AddController()
{
	if (m_nrCtrlrs < m_maxCtrlrs)
	{
		m_controllers.emplace_back(std::make_unique<Controller>(m_nrCtrlrs));
		m_nrCtrlrs++;
	}
}
