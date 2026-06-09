#pragma once
#include "Event.h"
namespace dae
{
	class GameObject;
	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void Notify(GameObject* sender, const Event& event) = 0;
	};
}
