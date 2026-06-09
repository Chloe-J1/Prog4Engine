#include "EventQueue.h"
#include <algorithm>
#include "IEventHandler.h"

void dae::EventQueue::AddEventHandler(IEventHandler* observer)
{
	m_eventHandlers.emplace_back(observer);
}

void dae::EventQueue::RemoveEventHandler(IEventHandler* observer)
{
	auto itr = std::find(m_eventHandlers.begin(), m_eventHandlers.end(), observer);

	if (itr != m_eventHandlers.end())
		*itr = nullptr;
}

void dae::EventQueue::Invoke(Event event)
{
	m_eventQueue.push(std::move(event));
}

void dae::EventQueue::Update()
{
	// Send events to all event handlers and then remove event from queue
	while (not m_eventQueue.empty())
	{
		for (size_t i = 0; i < m_eventHandlers.size(); ++i)
		{
			if (m_eventHandlers[i] != nullptr)
				m_eventHandlers[i]->Notify(m_eventQueue.front());
		}
		m_eventQueue.pop();
	}
}
