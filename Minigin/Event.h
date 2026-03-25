#pragma once
#include <cstdint>
#include "Pellets.h"
#include <memory>
// EVENT ARGS
//************
struct EventArg
{
	virtual ~EventArg() = default;
};

namespace dae
{
	class GameObject;
}
struct CollisionEvent : EventArg
{
	dae::GameObject* other;

	CollisionEvent(dae::GameObject* _other)
	{
		other = _other;
	}

	virtual ~CollisionEvent() = default;
};

struct PickupPelletEvent : EventArg
{
	dae::BasePellet* pellet;

	PickupPelletEvent(dae::BasePellet* _pellet)
	{
		pellet = _pellet;
	}

	virtual ~PickupPelletEvent() = default;
};


//************

enum class EventId
{
	PLAYER_DIED,
	PLAYER_TAKES_DAMAGE,
	ADD_SCORE,
	GAME_WON,
	HIT,
	PICKUP_PELLET
};

struct Event
{
	const EventId id;

	static const uint8_t maxArgs = 8;
	std::unique_ptr<EventArg> args[maxArgs];

	explicit Event(EventId _id):
		id{_id}
	{ }
};