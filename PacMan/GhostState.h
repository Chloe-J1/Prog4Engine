#pragma once
#include "../Minigin/Observer.h"
#include "../Minigin/Event.h"

namespace dae
{
	class GameObject;
}

namespace pacman
{
	class GhostComponent;
	class TargetMoverComponent;
	class GhostState
	{
	public:
		virtual ~GhostState() {};
		virtual std::unique_ptr<pacman::GhostState> Update(float) { return nullptr; };
		virtual void OnEnter(GhostComponent&) {};
		virtual void OnExit() {};
	};

	class ChaseState final : public GhostState, public dae::Observer
	{
	public:
		ChaseState();
		virtual std::unique_ptr<pacman::GhostState> Update(float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual void OnExit() override;
		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override;
	private:
		pacman::TargetMoverComponent* m_moveComp{};
		std::unique_ptr<GhostState> m_returnedState{nullptr};
	};

	class DizziedState final : public GhostState
	{
	public:
		DizziedState() = default;
		virtual std::unique_ptr<pacman::GhostState> Update(float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;
		virtual void OnExit() override;
	private:
		TargetMoverComponent* m_moveComp{};
		float m_dizziedTime{ 0.f };
		const float m_maxDizziedTime{ 5.f };
	};

	class EyeState final : public GhostState
	{
	public:
		EyeState();
		virtual std::unique_ptr<pacman::GhostState> Update(float elapsedSec) override;
		virtual void OnEnter(GhostComponent& ghost) override;
	};

}