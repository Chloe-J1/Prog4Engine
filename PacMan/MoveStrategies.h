#pragma once
// https://refactoring.guru/design-patterns/strategy

namespace pacman
{
	class TargetMoverComponent;
	class MovementBase
	{
	public:
		virtual ~MovementBase() = default;
		virtual void Move(float elapsedSec) = 0;
		void Init(TargetMoverComponent* moveComp);
	protected:
		TargetMoverComponent* m_moveComp;
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
}