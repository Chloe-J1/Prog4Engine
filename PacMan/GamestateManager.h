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

		void SetSoloButton(dae::GameObject* btn);
		void SetCoopButton(dae::GameObject* btn);
		void SetVersusButton(dae::GameObject* btn);
		void SetHomeButton(dae::GameObject* btn);
		dae::GameObject* GetSoloButton() const;
		dae::GameObject* GetCoopButton() const;
		dae::GameObject* GetVersusButton() const;
		dae::GameObject* GetHomeButton() const;
		void ClearButtons();
	private:
		std::unique_ptr<GameState> m_gameState{};
		int m_totalPellets{};

		dae::GameObject* m_soloButton{};
		dae::GameObject* m_coopButton{};
		dae::GameObject* m_versusButton{};
		dae::GameObject* m_homeButton{};
	};
}