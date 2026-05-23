#pragma once
#include "../Minigin/Event.h"
#include <glm/glm.hpp>
namespace pacman
{
	struct ScoreArg final : dae::EventArg
	{
		int score;

		ScoreArg(int _score);

		virtual ~ScoreArg() = default;
		ScoreArg(const ScoreArg& other) = delete;
		ScoreArg(ScoreArg&& other) = delete;
		ScoreArg& operator=(const ScoreArg& other) = delete;
		ScoreArg& operator=(ScoreArg&& other) = delete;
	};

	struct UpdateHealthArg final : dae::EventArg
	{
		int health;

		UpdateHealthArg(int _health);

		virtual ~UpdateHealthArg() = default;
		UpdateHealthArg(const UpdateHealthArg& other) = delete;
		UpdateHealthArg(UpdateHealthArg&& other) = delete;
		UpdateHealthArg& operator=(const UpdateHealthArg& other) = delete;
		UpdateHealthArg& operator=(UpdateHealthArg&& other) = delete;
	};

	struct DirectionChangedArg final : dae::EventArg
	{
		glm::vec2 direction;

		DirectionChangedArg(glm::vec2 _direction);

		virtual ~DirectionChangedArg() = default;
		DirectionChangedArg(const DirectionChangedArg& other) = delete;
		DirectionChangedArg(DirectionChangedArg&& other) = delete;
		DirectionChangedArg& operator=(const DirectionChangedArg& other) = delete;
		DirectionChangedArg& operator=(DirectionChangedArg&& other) = delete;
	};

	struct GhostDiedArg final : dae::EventArg
	{
		dae::GameObject* ghost;

		GhostDiedArg(dae::GameObject* _ghost);

		virtual ~GhostDiedArg() = default;
		GhostDiedArg(const GhostDiedArg& other) = delete;
		GhostDiedArg(GhostDiedArg&& other) = delete;
		GhostDiedArg& operator=(const GhostDiedArg& other) = delete;
		GhostDiedArg& operator=(GhostDiedArg&& other) = delete;
	};
}