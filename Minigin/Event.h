#pragma once
#include <cstdint>
struct EventArg{};

enum class EventId
{
	PLAYER_DIED,
	PLAYER_TAKES_DAMAGE,
	ADD_SCORE,
	GAME_WON
};

struct Event
{
	const EventId id;

	static const uint8_t MAX_ARGS = 8;
	EventArg args[MAX_ARGS];

	explicit Event(EventId _id):
		id{_id}
	{ }
};