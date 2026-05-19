#pragma once
#include "Observer.h"
#include <vector>

namespace dae
{
	class Subject
	{
	public:
		void AddObserver(Observer* observer);

		void RemoveObserver(Observer* observer);

		void NotifyObservers(GameObject* gameObject, Event event);
	private:
		std::vector<Observer*> m_observers;
	};
}
