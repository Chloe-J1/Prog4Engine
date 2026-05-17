#pragma once
#include "../Minigin/Singleton.h"
#include "GameState.h"
#include <memory>
#include "../Minigin/Observer.h"
namespace pacman
{
	class GamestateManager final : public dae::Singleton<GamestateManager>, public dae::Observer
	{
	public:
		GamestateManager();
		~GamestateManager();
		GamestateManager(const GamestateManager& other) = delete;
		GamestateManager(GamestateManager&& other) = delete;
		GamestateManager& operator=(const GamestateManager& other) = delete;
		GamestateManager& operator=(GamestateManager&& other) = delete;

		void Init();
		void SetTotalPellets(int value);
		int GetTotalPellets() const;
		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override;
	private:
		std::unique_ptr<GameState> m_gameState{};
		int m_totalPellets{};
	};
}