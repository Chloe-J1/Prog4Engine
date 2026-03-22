#pragma once
#include "Singleton.h"

#include <memory>
#include <vector>
#include "Controller.h"
#include <SDL3/SDL.h>
#include "InputData.h"

namespace dae
{
	

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		bool ProcessInput(float elapsedSec);

		void BindCommand(Input button, TriggerEvent triggerEvent, std::unique_ptr<Command> command, int controllerIdx);
		void UnbindCommand(Input button, TriggerEvent triggerEvent, int controllerIdx);
		void BindCommand(SDL_Scancode button, TriggerEvent triggerEvent, std::unique_ptr<Command> command);
		void UnbindCommand(SDL_Scancode button, TriggerEvent triggerEvent);

		void InitializeControllers(int amountOfControllers);
	private:
		
		bool IsDownThisFrame(SDL_Scancode button) const;
		bool IsReleasedThisFrame(SDL_Scancode button) const;
		bool IsHold(SDL_Scancode button) const;


		const bool* m_keyboardState{ nullptr };
		bool m_previousKeyboardState[SDL_SCANCODE_COUNT]{};

		std::vector<Bindings> m_keyboardBindings;
		
		std::vector<std::unique_ptr<Controller>> m_controllers;
		const int m_maxControllers{ 4 };
	};

}
