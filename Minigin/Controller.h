#pragma once
#include <memory>
#include <glm/vec2.hpp>
namespace dae
{
	class Controller
	{
	public:
#ifdef __EMSCRIPTEN__
		// SDL3
		enum class Input
		{
			DPad_Up = 11,
			DPad_Down = 12,
			DPad_Left = 13,
			DPad_Right = 14,

			//XBOX
			Button_A = 0,
			Button_B = 1,
			Button_Y = 3,
			Button_X = 2,

			Button_R1 = 10,
			Button_L1 = 9,
			Button_R = 8,
			Button_L = 7,
		};
#else	
		// XInput
		enum class Input
		{
			DPad_Up = 1,
			DPad_Down = 2,
			DPad_Left = 4,
			DPad_Right = 8,

			//XBOX
			Button_A = 4096,
			Button_B = 8192,
			Button_Y = 32768,
			Button_X = 16384,

			Button_R1 = 512,
			Button_L1 = 256,
			Button_R = 128,
			Button_L = 64
		};
#endif
		
	
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
	
	
