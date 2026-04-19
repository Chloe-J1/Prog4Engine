#pragma once
#include "Event.h"
#include "Singleton.h"
#include "Observer.h"
#include <vector>
#include <queue>
#include <algorithm>
#include "GameObject.h"

#include <iostream>
namespace dae
{
	class EventQueue : public Singleton<EventQueue>
	{
	public:
		void AddObserver(Observer* observer)
		{
			m_observers.emplace_back(observer);
		}

		void RemoveObserver(Observer* observer)
		{
			auto itr = std::find(m_observers.begin(), m_observers.end(), observer);

			if (itr != m_observers.end())
				m_observers.erase(itr);
		}

		void Invoke(Event event, GameObject* sender)
		{
			m_eventQueue.push(QueuedEventData{std::move(event), sender});
		}

		void Update()
		{
			// Send events to all observers and then remove event from queue
			while (not m_eventQueue.empty())
			{
				for (const auto& observer : m_observers)
				{
					observer->Notify(m_eventQueue.front().sender, m_eventQueue.front().event);
				}
				
				m_eventQueue.pop();
			}
		}

	private:
		struct QueuedEventData
		{
			Event event;
			GameObject* sender;
		};
		std::queue<QueuedEventData> m_eventQueue;
		std::vector<Observer*> m_observers;
	};
}