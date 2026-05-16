#pragma once
#include "../Minigin/Singleton.h"
#include "GameState.h"
#include <memory>
namespace pacman
{
	class GamestateManager final : public dae::Singleton<GamestateManager>
	{
	public:
		void Init();
	private:
		std::unique_ptr<GameState> m_gameState{};
	};
}