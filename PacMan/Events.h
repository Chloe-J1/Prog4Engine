#pragma once
#include "../Minigin/Event.h"
#include <glm/glm.hpp>
namespace pacman
{
	struct UpdateScoreArg : dae::EventArg
	{
		int score;

		UpdateScoreArg(int _score)
		{
			score = _score;
		}

		virtual ~UpdateScoreArg() = default;
	};

	struct UpdateHealthArg : dae::EventArg
	{
		int health;

		UpdateHealthArg(int _health)
		{
			health = _health;
		}

		virtual ~UpdateHealthArg() = default;
	};

	struct DirectionChangedArg : dae::EventArg
	{
		glm::vec2 direction;

		DirectionChangedArg(glm::vec2 _direction)
		{
			direction = _direction;
		}

		virtual ~DirectionChangedArg() = default;
	};
}