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
		nlohmann::json data;
		try
		{
			data = nlohmann::json::parse(iFile);
		}
		catch (const nlohmann::json::parse_error& e)
		{
			std::cerr << "JSON parse error in " << filename << ": " << e.what() << "\n";
			return m_scores;
		}
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

void pacman::HighscoreParser::UpdateScore(int score, int controllerIdx)
{
	std::filesystem::path filepath = std::filesystem::path(DATA_PATH) / "Scores.json";
	std::ifstream iFile(filepath);

	nlohmann::json data;
	try
	{
		data = nlohmann::json::parse(iFile);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		std::cerr << "JSON parse error in " << filepath << ": " << e.what() << "\n";
		return;
	}
	auto& currentPlayers = data["CurrentPlayers"];
	int prevScore{ currentPlayers[controllerIdx]["score"] };
	int newScore{ prevScore + score };
	currentPlayers[controllerIdx]["score"] = newScore;
	iFile.close();

	std::ofstream oFile(filepath);
	oFile << data.dump(4);
	oFile.close();
}

void pacman::HighscoreParser::UpdateHighscores()
{
	const int maxNrHighscores{ 3 };
	std::filesystem::path filepath = std::filesystem::path(DATA_PATH) / "Scores.json";
	std::ifstream iFile(filepath);
	nlohmann::json data;
	try
	{
		data = nlohmann::json::parse(iFile);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		std::cerr << "JSON parse error in " << filepath << ": " << e.what() << "\n";
		return;
	}
	iFile.close();

	auto& highscores = data["Highscores"];

	// Check for each player if they have reached a new highscore
	for (const auto& player : data["CurrentPlayers"])
	{
		int totalScore = player["score"];
		std::string playerName = player["name"];

		auto existingPlayerItr = std::find_if(highscores.begin(), highscores.end(), [&](const auto& player) {
			return player["name"] == playerName;
			});
		if (existingPlayerItr != highscores.end()) // update existing player
		{
			if(totalScore > (*existingPlayerItr)["score"])
				(*existingPlayerItr)["score"] = totalScore;
		}
		else if ((int)highscores.size() < maxNrHighscores) // less than 3 highscores
		{
			// insert new highscore
			highscores.push_back({
				{"name", playerName},
				{"score", totalScore}
				});
		}
		else // check if higher than highscores
		{
			if (highscores.back()["score"] < totalScore)
			{
				highscores.erase(highscores.end() - 1); // remove lowest
				// insert new highscore
				highscores.push_back({
					{"name", playerName},
					{"score", totalScore}
					});
			}
		}
		

		// sort highscores from high to low
		std::sort(highscores.begin(), highscores.end(), [](const auto& a, const auto& b) {
			return a["score"] > b["score"];
			});
	}

	std::ofstream oFile(filepath);
	oFile << data.dump(4);
}

void pacman::HighscoreParser::ClearCurrentPlayers()
{
	std::filesystem::path filePath = std::filesystem::path(DATA_PATH) / "Scores.json";

	std::ifstream iFile(filePath);
	nlohmann::json data;
	try
	{
		data = nlohmann::json::parse(iFile);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		std::cerr << "JSON parse error in " << filePath << ": " << e.what() << "\n";
		return;
	}
	iFile.close();

	data["CurrentPlayers"] = nlohmann::json::array();

	std::ofstream oFile(filePath);
	oFile << data.dump(4);
	oFile.close();
}

void pacman::HighscoreParser::ClearScores()
{
	std::filesystem::path filePath = std::filesystem::path(DATA_PATH) / "Scores.json";

	std::ifstream iFile(filePath);
	nlohmann::json data;
	try
	{
		data = nlohmann::json::parse(iFile);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		std::cerr << "JSON parse error in " << filePath << ": " << e.what() << "\n";
		return;
	}
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
