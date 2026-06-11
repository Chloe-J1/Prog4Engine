#pragma once
#include <string>
#include <vector>
#include "../Minigin/Singleton.h"
namespace pacman
{
	class HighscoreParser final : public dae::Singleton<HighscoreParser>
	{
	public:
		const std::vector<std::string>& GetScores(const std::string& type);
		void ClearCurrentPlayers();
		void ClearScores();
	private:
		std::vector<std::string> m_scores;
	};
}