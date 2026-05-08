#pragma once
#include "../Minigin/Event.h"
#include <memory>

namespace dae
{
	class GameObject;
	class SpriteComponent;
	class Hitbox;
}

namespace pacman
{
	class GhostComponent;
	class TargetMoverComponent;
	class MovementBase;
	
	class GhostState
	{
	public:
		virtual ~GhostState() {};
		virtual std::unique_ptr<pacman::GhostState> Update(pacman::GhostComponent&, float) { return nullptr; };
		virtual std::unique_ptr<pacman::GhostState> Notify(pacman::GhostComponent&, dae::GameObject*, const dae::Event&) { return nullptr; };
		virtual void OnEnter(GhostComponent&) {};
		virtual void OnExit(pacman::GhostComponent&) {};

	};

	class FollowTargetState final : public GhostState
	{
	public:
		FollowTargetState() = default;
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual std::unique_ptr<pacman::GhostState> Notify(pacman::GhostComponent& ghost, dae::GameObject* sender, const dae::Event& event) override;

	private:
		MovementBase* m_moveStrategy{nullptr};
	};

	class DizziedState final : public GhostState
	{
	public:
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual void OnExit(pacman::GhostComponent& ghost) override;

		virtual std::unique_ptr<pacman::GhostState> Notify(pacman::GhostComponent& ghost, dae::GameObject* sender, const dae::Event& event) override;
	private:
		TargetMoverComponent* m_moveComp{};
		dae::SpriteComponent* m_spriteComp{};
		dae::GameObject* m_ghost{};
		float m_dizziedTime{ 0.f };
		const float m_maxDizziedTime{ 5.f };
		const float m_almostDoneTime{ 3.f };
		std::unique_ptr<GhostState> m_returnedState{};
	};

	class EyeState final : public GhostState
	{
	public:
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual void OnExit(GhostComponent& ghost) override;
	private:
		TargetMoverComponent* m_moveComp{};
		const int m_targetIdx{ 418 };
		dae::Hitbox* m_hitbox{};
	};

	class IdleState final : public GhostState
	{
	public:
		virtual void OnEnter(GhostComponent& ghost) override;

	private:
		const int m_centerBoxIdx{ 480 };
	};

}