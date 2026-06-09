#include "Subject.h"
#include <algorithm>

void dae::Subject::AddObserver(IObserver* observer)
{
	m_observers.emplace_back(observer);
}

void dae::Subject::RemoveObserver(IObserver* observer)
{
	auto itr = std::find(m_observers.begin(), m_observers.end(), observer);

	if (itr != m_observers.end())
		m_observers.erase(itr);
}

void dae::Subject::NotifyObservers(GameObject* gameObject, Event event)
{
	for (auto observer : m_observers)
	{
		observer->Notify(gameObject, event);
	}
}
