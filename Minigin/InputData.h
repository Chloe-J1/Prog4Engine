#pragma once
#include <memory>
#include "Commands.h"
#include <SDL3/SDL.h>
namespace dae
{
	enum class TriggerEvent
	{
		PressedThisFrame,
		ReleasedThisFrame,
		Hold
	};
	


	/*#ifdef __EMSCRIPTEN__*/
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
	//#else	
	//// XInput
	//enum class Input
	//{
	//	DPad_Up = 1,
	//	DPad_Down = 2,
	//	DPad_Left = 4,
	//	DPad_Right = 8,

	//	//XBOX
	//	Button_A = 4096,
	//	Button_B = 8192,
	//	Button_Y = 32768,
	//	Button_X = 16384,

	//	Button_R1 = 512,
	//	Button_L1 = 256,
	//	Button_R = 128,
	//	Button_L = 64
	//};
	//#endif

	struct Bindings
	{
		Bindings(SDL_Scancode sdlScancode, TriggerEvent _triggerEvent, std::unique_ptr<Command> _command) :
			keyboardInput(sdlScancode),
			triggerEvent(_triggerEvent),
			command(std::move(_command))
		{
		}
		Bindings(Input controllerInput, TriggerEvent _triggerEvent, std::unique_ptr<Command> _command) :
			ctrlInput(controllerInput),
			triggerEvent(_triggerEvent),
			command(std::move(_command))
		{
		}

		SDL_Scancode keyboardInput{}; // keyboard input
		Input ctrlInput{}; // controller input
		TriggerEvent triggerEvent;
		std::unique_ptr<Command> command;
	};
}
