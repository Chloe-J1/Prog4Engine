#pragma once
#include "../Minigin/Event.h"
#include <glm/glm.hpp>
namespace pacman
{
	struct ScoreArg final : dae::EventArg
	{
		int score;
		dae::GameObject* sender;

		ScoreArg(int _score, dae::GameObject* _sender);

		virtual ~ScoreArg() = default;
		ScoreArg(const ScoreArg& other) = delete;
		ScoreArg(ScoreArg&& other) = delete;
		ScoreArg& operator=(const ScoreArg& other) = delete;
		ScoreArg& operator=(ScoreArg&& other) = delete;
	};

	struct UpdateHealthArg final : dae::EventArg
	{
		int health;
		dae::GameObject* sender;

		UpdateHealthArg(int _health, dae::GameObject* _sender);

		virtual ~UpdateHealthArg() = default;
		UpdateHealthArg(const UpdateHealthArg& other) = delete;
		UpdateHealthArg(UpdateHealthArg&& other) = delete;
		UpdateHealthArg& operator=(const UpdateHealthArg& other) = delete;
		UpdateHealthArg& operator=(UpdateHealthArg&& other) = delete;
	};

	struct DirectionChangedArg final : dae::EventArg
	{
		glm::vec2 direction;
		dae::GameObject* sender;

		DirectionChangedArg(glm::vec2 _direction, dae::GameObject* _sender);

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

	struct SenderArg final : dae::EventArg
	{
		dae::GameObject* sender;

		SenderArg(dae::GameObject* _sender);
		virtual ~SenderArg() = default;
		SenderArg(const SenderArg& other) = delete;
		SenderArg(SenderArg&& other) = delete;
		SenderArg& operator=(const SenderArg& other) = delete;
		SenderArg& operator=(SenderArg&& other) = delete;
	};
}