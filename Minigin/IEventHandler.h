#pragma once
#include "Event.h"
namespace dae
{
	class IEventHandler
	{
	public:
		virtual ~IEventHandler() = default;
		virtual void Notify(const Event& event) = 0;
	};
}