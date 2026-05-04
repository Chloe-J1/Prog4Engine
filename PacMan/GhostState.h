#pragma once

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

	class ChaseState final : public GhostState
	{
	public:
		ChaseState(dae::SpriteComponent* spriteComp, TargetMoverComponent* moveComp);
		virtual GhostState* Update(float elapsedSec) override;
		virtual void OnEnter() override;
	private:
		dae::SpriteComponent* m_spriteComp;
		pacman::TargetMoverComponent* m_moveComp;
	};

	class DizziedState final : public GhostState
	{
	public:
		DizziedState(dae::SpriteComponent* spriteComp, TargetMoverComponent* moveComp);
		virtual GhostState* Update(float elapsedSec) override;
		virtual void OnEnter() override;
	private:
		dae::SpriteComponent* m_spriteComp;
		TargetMoverComponent* m_moveComp;
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