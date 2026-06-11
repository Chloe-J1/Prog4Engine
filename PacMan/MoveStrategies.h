#pragma once
// https://refactoring.guru/design-patterns/strategy

namespace pacman
{
	class TargetMoverComponent;
	class PlayerMovement;
	class MovementBase
	{
	public:
		virtual ~MovementBase() = default;
		virtual void OnEnter();
		virtual void Move(float elapsedSec);
		virtual void OnExit();
		void Init(TargetMoverComponent* moveComp);
	protected:
		TargetMoverComponent* m_moveComp{};
	};

	class ChaseMovement final : public MovementBase
	{
	public:
		virtual void Move(float elapsedSec) override;
	};

	class CornerMovement final : public MovementBase
	{
	public:
		virtual void Move(float elapsedSec) override;
	};

	class FleeMovement final : public MovementBase
	{
	public:
		virtual void Move(float elapsedSec) override;
	};

	class SueMovement final : public MovementBase
	{
	public:
		virtual void Move(float elapsedSec) override;

	private:
		float m_fleeTimer{};
		const float m_maxTime{};
		bool m_isFleeing{ false };
	};

	class NonAIMovement final : public MovementBase
	{
	public:
		virtual void OnEnter() override;
		virtual void OnExit() override;
		void Init(PlayerMovement* playerMovementComp);
	private:
		PlayerMovement* m_playerMovement{};
	};
}