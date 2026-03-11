#pragma once
#include <memory>
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
		~Controller();
		Controller(Controller&&) = delete;
		Controller& operator=(Controller&&) = delete;
		Controller(const Controller&) = delete;
		Controller& operator=(const Controller&) = delete;

	
		void ProcessInput();
	
		bool IsDownThisFrame(Input button) const;
		bool IsReleasedThisFrame(Input button) const;
		bool IsHold(Input button) const;
		glm::vec2 GetRightStickValues() const;
		glm::vec2 GetLeftStickValues() const;
	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pImpl;
	};
}
	
	
