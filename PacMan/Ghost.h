#pragma once
#include "../Minigin/Component.h"
#include "GameObject.h"
namespace pacman
{
	class Ghost : public dae::Component
	{
	public:
		Ghost(dae::GameObject* owner) :
			Component(owner)
		{
		}
	};
}