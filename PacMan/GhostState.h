#pragma once
#include "../Minigin/Observer.h"
#include "../Minigin/Event.h"

namespace dae
{
	class SpriteComponent;
	class GameObject;
}

namespace pacman
{
	class TargetMoverComponent;
	class GhostState
	{
	public:
		virtual ~GhostState() {};
		virtual GhostState* Update(float) { return nullptr; };
		virtual void OnEnter() {};
		virtual void OnExit() {};
	};

	class ChaseState final : public GhostState, public dae::Observer
	{
	public:
		ChaseState(dae::SpriteComponent* spriteComp, TargetMoverComponent* moveComp);
		virtual GhostState* Update(float elapsedSec) override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override;
	private:
		dae::SpriteComponent* m_spriteComp;
		pacman::TargetMoverComponent* m_moveComp;
		GhostState* m_returnedState{nullptr};
	};

	class DizziedState final : public GhostState
	{
	public:
		DizziedState(dae::SpriteComponent* spriteComp, TargetMoverComponent* moveComp);
		virtual GhostState* Update(float elapsedSec) override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		dae::SpriteComponent* m_spriteComp;
		TargetMoverComponent* m_moveComp;
		float m_dizziedTime{ 0.f };
		const float m_maxDizziedTime{ 5.f };
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