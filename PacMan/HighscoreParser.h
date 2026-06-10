#pragma once
#include <string>
#include <vector>
namespace pacman
{
	class HighscoreParser final
	{
	public:
		const std::vector<std::string>& GetScores(const std::string& type);
		void ClearCurrentPlayers();
		void ClearScores();
	private:
		std::vector<std::string> m_scores;
	};
}