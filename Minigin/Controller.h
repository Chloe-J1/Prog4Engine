#pragma once
#include <memory>
#include "InputData.h"
#include <map>

namespace dae
{
	class Controller
	{
	public:
			
		Controller(int index);
		~Controller();
		Controller(Controller&&) = delete;
		Controller& operator=(Controller&&) = delete;
		Controller(const Controller&) = delete;
		Controller& operator=(const Controller&) = delete;

	
		void ProcessInput(float elapsedSec);

		void BindCommand(Input button, TriggerEvent triggerEvent, std::unique_ptr<Command> command);
		void UnbindCommand(Input button);
	
		bool IsDownThisFrame(Input button) const;
		bool IsReleasedThisFrame(Input button) const;
		bool IsHold(Input button) const;
		glm::vec2 GetRightStickValues() const;
		glm::vec2 GetLeftStickValues() const;
	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pImpl;
		std::map<Input, Bindings> m_controllerMap;
	};
}
	
	
