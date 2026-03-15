#pragma once
namespace dae
{
	enum class Event
	{
		PLAYER_DIED,
		PLAYER_TAKES_DAMAGE,
		ADD_SCORE,
		GAME_WON
	};
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(GameObject* gameObject, Event event) = 0;
	};
}
