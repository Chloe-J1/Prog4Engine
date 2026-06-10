#include "HighscoreParser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

const std::vector<std::string>& pacman::HighscoreParser::GetScores(const std::string& type)
{
	std::filesystem::path filename = std::filesystem::path(DATA_PATH) / "Scores.json";
	std::ifstream iFile(filename);

	if (iFile.is_open())
	{
		nlohmann::json data = nlohmann::json::parse(iFile);
		std::string highscoreText{};
		m_scores.clear();
		
		for (const auto& line : data[type])
		{
			highscoreText = line["name"].get<std::string>() + " " + std::to_string(line["score"].get<int>());
			m_scores.push_back(highscoreText);
		}

		iFile.close();
	}
	else
	{
		std::cerr << "Can't open file " << filename << "\n";
	}


	return m_scores;
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
	oFile.close();
}

void pacman::HighscoreParser::ClearScores()
{
	std::filesystem::path filePath = std::filesystem::path(DATA_PATH) / "Scores.json";

	nlohmann::json data;
	std::ifstream iFile(filePath);
	data = nlohmann::json::parse(iFile);
	iFile.close();

	auto& players = data["CurrentPlayers"];
	for (auto& player : players)
	{
		player["score"] = 0;
	}

	std::ofstream oFile(filePath);
	oFile << data.dump(4);
	oFile.close();
}
