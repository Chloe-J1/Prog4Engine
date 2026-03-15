#pragma once
#include "Observer.h"
#include <vector>
#include <algorithm>
namespace dae
{
	class Subject
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

	//protected:
		void NotifyObservers(GameObject* gameObject, Event event)
		{
			for (auto observer : m_observers)
			{
				observer->Notify(gameObject, event);
			}
		}
	private:
		std::vector<Observer*> m_observers;
	};
}
