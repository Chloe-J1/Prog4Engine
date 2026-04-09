#include <SDL3/SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl3.h"
#include <iostream>
#include <algorithm>


dae::InputManager::InputManager()
{
	m_keyboardState = SDL_GetKeyboardState(nullptr);
	
}

bool dae::InputManager::ProcessInput(float elapsedSec)
{
	// XINPUT -> controller
	//********
	
	for (const auto& controller : m_controllers)
	{
		controller->ProcessInput(elapsedSec);
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
	

	for (const auto& commands : m_keyboardBindings)
	{
		switch (commands.triggerEvent)
		{
		case dae::TriggerEvent::Hold:
			if (IsHold(commands.keyboardInput))
				commands.command->Execute(elapsedSec);
			break;
		case dae::TriggerEvent::PressedThisFrame:
			if (IsDownThisFrame(commands.keyboardInput))
				commands.command->Execute(elapsedSec);
			break;
		case dae::TriggerEvent::ReleasedThisFrame:
			if (IsReleasedThisFrame(commands.keyboardInput))
				commands.command->Execute(elapsedSec);
			break;
		}
	}

	
	return true;
}

void dae::InputManager::BindCommand(Input button, TriggerEvent triggerEvent, std::unique_ptr<Command> command, int controllerIdx)
{
	m_controllers[controllerIdx]->BindCommand(button, triggerEvent, std::move(command));
}

void dae::InputManager::UnbindCommand(Input button, TriggerEvent triggerEvent, int controllerIdx)
{
	m_controllers[controllerIdx]->UnbindCommand(button, triggerEvent);
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
	return m_keyboardState[button];
}

void dae::InputManager::BindCommand(SDL_Scancode button, TriggerEvent triggerEvent, std::unique_ptr<Command> command)
{
	m_keyboardBindings.emplace_back(Bindings{ button, triggerEvent, std::move(command) });
}

void dae::InputManager::UnbindCommand(SDL_Scancode button, TriggerEvent triggerEvent)
{
	auto itr = std::find_if(m_keyboardBindings.begin(), m_keyboardBindings.end(), [=](const Bindings& binding) { return binding.keyboardInput == button && binding.triggerEvent == triggerEvent; });
	if (itr == m_keyboardBindings.end()) return; // no such binding found
	m_keyboardBindings.erase(itr);
}

void dae::InputManager::UnbindAllCommands()
{
	m_keyboardBindings.clear();
	for (const auto& controller : m_controllers)
	{
		controller->UnbindAllCommands();
	}
}

void dae::InputManager::InitializeControllers(int amountOfControllers)
{
	if (amountOfControllers > m_maxControllers)
		throw std::invalid_argument("Error: Don't initialize more than 4 controllers!\n");
		
	for (int index = 0; index < amountOfControllers; index++)
	{
		m_controllers.emplace_back(std::make_unique<Controller>(index));
	}
}
