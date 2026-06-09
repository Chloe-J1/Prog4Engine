#pragma once
#include "IObserver.h"
#include <vector>

namespace dae
{
	class Subject
	{
	public:
		void AddObserver(IObserver* observer);

		void RemoveObserver(IObserver* observer);

		void NotifyObservers(GameObject* gameObject, Event event);
	private:
		std::vector<IObserver*> m_observers;
	};
}
