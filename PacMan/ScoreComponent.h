#pragma once
#include "Component.h"
#include "../Minigin/EventQueue.h"
#include "../Minigin/IEventHandler.h"

namespace pacman
{
	class ScoreComponent final : public dae::Component, public dae::IEventHandler
	{
	public:
		ScoreComponent(dae::GameObject* owner, int controllerIdx);
		~ScoreComponent();
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		int GetScore() const;

		
		virtual void OnCollision(dae::GameObject* other) override;
		virtual void Notify(const dae::Event& event) override;

	private:
		int m_score{ 0 };
		static int m_nrGhostsEaten;
		dae::EventQueue& m_eventQueue{ dae::EventQueue::GetInstance() };
		int m_controllerIdx;


		void CheckForHighscore();
	};
}
