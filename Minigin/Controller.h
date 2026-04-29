#pragma once
#include <memory>
#include "InputData.h"
#include <vector>

namespace dae
{
	class Controller final
	{
	public:
			
		Controller(int index);
		~Controller();
		Controller(Controller&&) = delete;
		Controller& operator=(Controller&&) = delete;
		Controller(const Controller&) = delete;
		Controller& operator=(const Controller&) = delete;

	
		void ProcessInput();

		void BindCommand(Input button, TriggerEvent triggerEvent, std::unique_ptr<Command> command);
		void UnbindCommand(Input button, TriggerEvent triggerEvent);
		void UnbindAllCommands();
	
		bool IsDownThisFrame(Input button) const;
		bool IsReleasedThisFrame(Input button) const;
		bool IsHold(Input button) const;
		glm::vec2 GetRightStickValues() const;
		glm::vec2 GetLeftStickValues() const;
	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_impl;
		std::vector<Bindings> m_controllerBindings;
	};
}
	
	
