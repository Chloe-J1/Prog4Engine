#pragma once
#include <memory>
namespace dae
{
	class GameObject;
	// EVENT ARGS
	//************
	struct EventArg
	{
		virtual ~EventArg() = default;
	};

	//************

	enum class EventId
	{
		PLAYER_DIED,
		PLAYER_TAKES_DAMAGE,
		UPDATE_SCORE,
		GAME_WON,
		DIRECTION_CHANGED
	};

	struct Event
	{
		const EventId id;
		std::unique_ptr<EventArg> arg;

		explicit Event(EventId _id) :
			id{ _id }
		{
		}
	};
}
