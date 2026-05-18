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
				*itr = nullptr;
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
				for (size_t i = 0; i < m_observers.size(); ++i)
				{
					if (m_observers[i] != nullptr)
						m_observers[i]->Notify(m_eventQueue.front().sender, m_eventQueue.front().event);
				}
				std::erase(m_observers, nullptr);
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
		std::vector<Observer*> m_observers{};
	};
}