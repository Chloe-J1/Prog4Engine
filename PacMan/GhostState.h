#pragma once
#include "../Minigin/Observer.h"
#include "../Minigin/Event.h"

namespace dae
{
	class GameObject;
	class SpriteComponent;
}

namespace pacman
{
	class GhostComponent;
	class TargetMoverComponent;
	
	class GhostState
	{
	public:
		virtual ~GhostState() {};
		virtual std::unique_ptr<pacman::GhostState> Update(pacman::GhostComponent&, float) { return nullptr; };
		virtual void OnEnter(GhostComponent&) {};
		virtual void OnExit(pacman::GhostComponent&) {};
	};

	class ChaseState final : public GhostState, public dae::Observer
	{
	public:
		ChaseState();
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual void OnExit(pacman::GhostComponent& ghost) override;
		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override;
	private:
		pacman::TargetMoverComponent* m_moveComp{};
		std::unique_ptr<GhostState> m_returnedState{nullptr};
	};

	class CornerState final : public GhostState, public dae::Observer
	{
	public:
		CornerState();
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual void OnExit(pacman::GhostComponent& ghost) override;
		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override;
	private:
		pacman::TargetMoverComponent* m_moveComp{};
		std::unique_ptr<GhostState> m_returnedState{ nullptr };
	};

	class SueState final : public GhostState, public dae::Observer
	{
	public:
		SueState();
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual void OnExit(pacman::GhostComponent& ghost) override;
		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override;
	private:
		pacman::TargetMoverComponent* m_moveComp{};
		std::unique_ptr<GhostState> m_returnedState{ nullptr };
		float m_fleeTimer{0.f};
		const float m_maxTime{ 8.f };
		bool m_isFleeing{ false };
	};

	class DizziedState final : public GhostState, public dae::Observer
	{
	public:
		DizziedState() = default;
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual void OnExit(pacman::GhostComponent& ghost) override;

		virtual void Notify(dae::GameObject* sender, const dae::Event& event);
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
		EyeState();
		virtual std::unique_ptr<pacman::GhostState> Update(GhostComponent& ghost, float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;

	private:
		TargetMoverComponent* m_moveComp{};
		const int m_targetIdx{ 418 };
	};

	class IdleState final : public GhostState
	{
	public:
		virtual void OnEnter(GhostComponent& ghost) override;

	private:
		const int m_centerBoxIdx{ 480 };
	};

}