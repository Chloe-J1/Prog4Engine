#pragma once
#include <memory>
#include <glm/glm.hpp>
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

struct DirectionChangedArg : EventArg
{
	glm::vec2 direction;

	DirectionChangedArg(glm::vec2 _direction)
	{
		direction = _direction;
	}

	virtual ~DirectionChangedArg() = default;
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

	explicit Event(EventId _id):
		id{_id}
	{ }
};