#include "InputData.h"

dae::Bindings::Bindings(SDL_Scancode sdlScancode, TriggerEvent _triggerEvent, std::unique_ptr<Command> _command) :
	keyboardInput(sdlScancode),
	triggerEvent(_triggerEvent),
	command(std::move(_command))
{
}

dae::Bindings::Bindings(Input controllerInput, TriggerEvent _triggerEvent, std::unique_ptr<Command> _command) :
	ctrlInput(controllerInput),
	triggerEvent(_triggerEvent),
	command(std::move(_command))
{
}
