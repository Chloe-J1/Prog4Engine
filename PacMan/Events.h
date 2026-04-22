#pragma once
#include "../Minigin/Event.h"
#include <glm/glm.hpp>
namespace pacman
{
	struct UpdateScoreArg : dae::EventArg
	{
		int score;

		UpdateScoreArg(int _score):
			score{_score}
		{
		}

		virtual ~UpdateScoreArg() = default;
		UpdateScoreArg(const UpdateScoreArg& other) = delete;
		UpdateScoreArg(UpdateScoreArg&& other) = delete;
		UpdateScoreArg& operator=(const UpdateScoreArg& other) = delete;
		UpdateScoreArg& operator=(UpdateScoreArg&& other) = delete;
	};

	struct UpdateHealthArg : dae::EventArg
	{
		int health;

		UpdateHealthArg(int _health):
			health{_health}
		{
		}

		virtual ~UpdateHealthArg() = default;
		UpdateHealthArg(const UpdateHealthArg& other) = delete;
		UpdateHealthArg(UpdateHealthArg&& other) = delete;
		UpdateHealthArg& operator=(const UpdateHealthArg& other) = delete;
		UpdateHealthArg& operator=(UpdateHealthArg&& other) = delete;
	};

	struct DirectionChangedArg : dae::EventArg
	{
		glm::vec2 direction;

		DirectionChangedArg(glm::vec2 _direction):
			direction{_direction}
		{
		}

		virtual ~DirectionChangedArg() = default;
		DirectionChangedArg(const DirectionChangedArg& other) = delete;
		DirectionChangedArg(DirectionChangedArg&& other) = delete;
		DirectionChangedArg& operator=(const DirectionChangedArg& other) = delete;
		DirectionChangedArg& operator=(DirectionChangedArg&& other) = delete;
	};
}