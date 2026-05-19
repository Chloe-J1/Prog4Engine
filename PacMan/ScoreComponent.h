#pragma once
#include "Component.h"
#include "Subject.h"


#include "../Minigin/EventQueue.h"

namespace pacman
{
	class ScoreComponent : public dae::Component
	{
	public:
		ScoreComponent(dae::GameObject* owner);

		dae::Subject* GetSubject();

		int GetScore() const;

		
		virtual void OnCollision(dae::GameObject* other) override;

	private:
		int m_score{ 0 };
		std::unique_ptr<dae::Subject> m_updateScoreEvent;
	};
}
