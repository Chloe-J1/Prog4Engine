#pragma once
#include "../Minigin/Component.h"
#include "GameObject.h"
#include "GhostState.h"
#include <memory>
#include "../Minigin/Observer.h"
#include <vector>
#include "MoveStrategies.h"

namespace pacman
{
	class GhostComponent final : public dae::Component, public dae::Observer
	{
	public:
		GhostComponent(dae::GameObject* owner, std::unique_ptr<MovementBase> moveStrategy);
		~GhostComponent();
		GhostComponent(const GhostComponent& other) = delete;
		GhostComponent(GhostComponent&& other) = delete;
		GhostComponent& operator=(const GhostComponent& other) = delete;
		GhostComponent& operator=(GhostComponent&& other) = delete;

		int GetDamage() const;
		void AddTarget(dae::GameObject* target);
		MovementBase* GetMoveStrategy();

		virtual void Update(float elapsedSec) override;

		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override;
	private:
		int m_damage;
		std::unique_ptr<GhostState> m_ghostState;
		std::unique_ptr<MovementBase> m_moveStrategy;
		std::vector<dae::GameObject*> m_targets;

		void RemoveTarget(dae::GameObject* target);
	};
}