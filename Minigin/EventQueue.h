#pragma once
#include "Event.h"
#include "Singleton.h"
#include <vector>
#include <queue>
#include "GameObject.h"


namespace dae
{
	class Observer;
	class EventQueue : public Singleton<EventQueue>
	{
	public:
		void AddObserver(Observer* observer);

		void RemoveObserver(Observer* observer);

		void Invoke(Event event, GameObject* sender);


		void Update();
	private:
		struct QueuedEventData
		{
			Event event;
			GameObject* sender;
		};
		std::queue<QueuedEventData> m_eventQueue;
		std::vector<Observer*> m_observers{};
	};
}