#include "EventQueue.h"
#include <algorithm>
#include "IObserver.h"

void dae::EventQueue::AddObserver(IObserver* observer)
{
	m_observers.emplace_back(observer);
}

void dae::EventQueue::RemoveObserver(IObserver* observer)
{
	auto itr = std::find(m_observers.begin(), m_observers.end(), observer);

	if (itr != m_observers.end())
		*itr = nullptr;
}

void dae::EventQueue::Invoke(Event event, GameObject* sender)
{
	m_eventQueue.push(QueuedEventData{ std::move(event), sender });
}

void dae::EventQueue::Update()
{
	// Send events to all observers and then remove event from queue
	while (not m_eventQueue.empty())
	{
		for (size_t i = 0; i < m_observers.size(); ++i)
		{
			if (m_observers[i] != nullptr)
				m_observers[i]->Notify(m_eventQueue.front().sender, m_eventQueue.front().event);
		}
		m_eventQueue.pop();
	}
}
