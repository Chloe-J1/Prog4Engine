#pragma once
#include <string>
#include <vector>
namespace pacman
{
	class HighscoreParser final
	{
	public:
		const std::vector<std::string>& GetHighscores();
		void ClearCurrentPlayers();
	private:
		std::vector<std::string> m_highscores;
	};
}