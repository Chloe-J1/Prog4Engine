#include "HighscoreParser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

const std::vector<std::string>& pacman::HighscoreParser::GetHighscores()
{
	std::filesystem::path filename = std::filesystem::path(DATA_PATH) / "Scores.json";
	std::ifstream iFile(filename);

	if (iFile.is_open())
	{
		nlohmann::json data = nlohmann::json::parse(iFile);
		std::string highscoreText{};
		
		for (const auto& line : data["Highscores"])
		{
			highscoreText = line["name"].get<std::string>() + " " + std::to_string(line["score"].get<int>());
			m_highscores.push_back(highscoreText);
		}

		iFile.close();
	}
	else
	{
		std::cerr << "Can't open file " << filename << "\n";
	}


	return m_highscores;
}

void pacman::HighscoreParser::ClearCurrentPlayers()
{
	std::filesystem::path filePath = std::filesystem::path(DATA_PATH) / "Scores.json";

	nlohmann::json data;
	std::ifstream iFile(filePath);
	data = nlohmann::json::parse(iFile);
	iFile.close();

	data["CurrentPlayers"] = nlohmann::json::array();

	std::ofstream oFile(filePath);
	oFile << data.dump(4);
}
