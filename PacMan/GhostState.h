#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class SpriteComponent;
	class GameObject;
}

namespace pacman
{
	enum class Direction
	{
		right,
		left,
		up,
		down
	};
	class GhostState
	{
	public:
		virtual ~GhostState() {};
		virtual GhostState* Update(float) { return nullptr; };
		virtual void OnEnter() {};
		virtual void OnExit() {};
	};

	class MoveTargetState : public GhostState
	{
	public:
		MoveTargetState(dae::GameObject* ghost, dae::GameObject* targetState);
		virtual ~MoveTargetState() {};
		virtual GhostState* Update(float elapsedSec) override;

		void SetTarget(dae::GameObject* targetObj);
	private:
		float m_moveSpeed{ 50.f };
		dae::GameObject* m_targetObj{};
		glm::vec2 m_nextDir{ 0,-1 };
		int m_gridIdx{};
		std::vector<int> m_neighbors;
		Direction m_dir{ Direction::up };
		dae::GameObject* m_ghost{};

		void ChangeDirection();
		void MoveInDirection(float elapsedSec);
	};

	class ChaseState final : public MoveTargetState
	{
	public:
		ChaseState(dae::GameObject* ghost, dae::SpriteComponent* spriteComp, dae::GameObject* targetState);
		virtual GhostState* Update(float elapsedSec) override;
		virtual void OnEnter() override;
	private:
		dae::SpriteComponent* m_spriteComp;

	};

	class DizziedState final : public MoveTargetState
	{
	public:
		DizziedState(dae::GameObject* ghost, dae::SpriteComponent* spriteComp, dae::GameObject* targetState);
		virtual GhostState* Update(float elapsedSec) override;
		virtual void OnEnter() override;
	private:
		dae::SpriteComponent* m_spriteComp;
	};

	class EyeState final : public GhostState
	{
	public:
		EyeState(dae::SpriteComponent* spriteComp);
		virtual GhostState* Update(float elapsedSec) override;
		virtual void OnEnter() override;

	private:
		dae::SpriteComponent* m_spriteComp;
	};

}