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
		virtual void OnEnter(GhostComponent&) {};
		virtual std::unique_ptr<pacman::GhostState> Update(pacman::GhostComponent&, float) { return nullptr; };
		virtual std::unique_ptr<pacman::GhostState> Notify(pacman::GhostComponent&, dae::GameObject*, const dae::Event&) { return nullptr; };
		virtual void OnExit(pacman::GhostComponent&) {};

	};

	class FollowTargetState final : public GhostState
	{
	public:
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual std::unique_ptr<pacman::GhostState> Notify(pacman::GhostComponent& ghost, dae::GameObject* sender, const dae::Event& event) override;
		virtual void OnExit(pacman::GhostComponent&) override;

	private:
		MovementBase* m_moveStrategy{nullptr};
		dae::SpriteComponent* m_spriteComp{};
	};

	class DizziedState final : public GhostState
	{
	public:
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual void OnExit(pacman::GhostComponent& ghost) override;

		virtual std::unique_ptr<pacman::GhostState> Notify(pacman::GhostComponent& ghost, dae::GameObject* sender, const dae::Event& event) override;
	private:
		TargetMoverComponent* m_moveComp{};
		MovementBase* m_moveStrategy{ nullptr };
		bool m_isNonAIStrategy{ false };
		dae::SpriteComponent* m_spriteComp{};
		dae::GameObject* m_ghost{};
		float m_dizziedTime{ 0.f };
		const float m_maxDizziedTime{ 5.f };
		const float m_almostDoneTime{ 3.f };
	};

	class EyeState final : public GhostState
	{
	public:
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
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