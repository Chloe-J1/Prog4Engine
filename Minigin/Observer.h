#pragma once
#include "Event.h"
namespace dae
{
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(GameObject* sender, const Event& event) = 0;
	};
}
