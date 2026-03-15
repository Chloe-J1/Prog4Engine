#pragma once
namespace dae
{
	enum class Event
	{
		PLAYER_DIED,
		PLAYER_TAKES_DAMAGE
	};
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(GameObject* gameObject, Event event) = 0;
	};
}
