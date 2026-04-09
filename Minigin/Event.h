#pragma once
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

struct UpdateScoreArg : EventArg
{
	int score;

	UpdateScoreArg(int _score)
	{
		score = _score;
	}

	virtual ~UpdateScoreArg() = default;
};

struct UpdateHealthArg : EventArg
{
	int health;

	UpdateHealthArg(int _health)
	{
		health = _health;
	}

	virtual ~UpdateHealthArg() = default;
};


//************

enum class EventId
{
	PLAYER_DIED,
	PLAYER_TAKES_DAMAGE,
	UPDATE_SCORE,
	GAME_WON
};

struct Event
{
	const EventId id;
	std::unique_ptr<EventArg> arg;

	explicit Event(EventId _id):
		id{_id}
	{ }
};