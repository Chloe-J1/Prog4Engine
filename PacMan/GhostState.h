#pragma once
#include "../Minigin/Event.h"
#include "../Minigin/EventQueue.h"
#include <memory>
#include <glm/glm.hpp>
#include "Graph.h"

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
		virtual ~GhostState() = default;
		virtual void OnEnter(GhostComponent&);
		virtual std::unique_ptr<pacman::GhostState> Update(pacman::GhostComponent& ghost, float elapsedSec);
		virtual std::unique_ptr<pacman::GhostState> Notify(pacman::GhostComponent& ghost, const dae::Event& event);
		virtual std::unique_ptr<pacman::GhostState> OnCollision(pacman::GhostComponent& ghost, dae::GameObject* other);
		virtual void OnExit(pacman::GhostComponent& ghost);
	};

	class FollowTargetState final : public GhostState
	{
	public:
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual std::unique_ptr<pacman::GhostState> Notify(pacman::GhostComponent& ghost, const dae::Event& event) override;
		virtual void OnExit(pacman::GhostComponent&) override;

	private:
		MovementBase* m_moveStrategy{nullptr};
		dae::SpriteComponent* m_spriteComp{};
	};

	class DizziedState final : public GhostState
	{
	public:
		void OnEnter(GhostComponent& ghost);
		std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec);
		void OnExit(pacman::GhostComponent& ghost);

		std::unique_ptr<pacman::GhostState> OnCollision(pacman::GhostComponent& ghost, dae::GameObject* other);
	private:
		TargetMoverComponent* m_moveComp{};
		MovementBase* m_moveStrategy{ nullptr };
		bool m_isNonAIStrategy{ false };
		dae::SpriteComponent* m_spriteComp{};
		dae::GameObject* m_ghost{};
		float m_dizziedTime{ 0.f };
		const float m_maxDizziedTime{ 100.f };
		const float m_almostDoneTime{ 3.f };
		dae::EventQueue& m_eventQueue{ dae::EventQueue::GetInstance() };
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

	class DeathState final : public GhostState
	{
	public:
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual void OnExit(GhostComponent& ghost) override;
	private:
		TargetMoverComponent* m_moveComp{};
		const int m_centerBoxIdx{ 480 };
		float m_timer{};
		const float m_maxDeathTime{ float(rand() % 3) + 5.f};
		glm::vec2 m_respawnPos{Graph::GetInstance().GetWorldPos(419)};
	};

}