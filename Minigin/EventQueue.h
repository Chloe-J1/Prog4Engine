#pragma once
#include "Event.h"
#include "Singleton.h"
#include <vector>
#include <queue>
#include "GameObject.h"


namespace dae
{
	class IEventHandler;
	class EventQueue : public Singleton<EventQueue>
	{
	public:
		void AddEventHandler(IEventHandler* observer);

		void RemoveEventHandler(IEventHandler* observer);

		void Invoke(Event event);


		void Update();
	private:
		std::queue<Event> m_eventQueue;
		std::vector<IEventHandler*> m_eventHandlers{};
	};
}