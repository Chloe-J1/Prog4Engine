#pragma once
#include <memory>
#include "../Minigin/Event.h"
#include "../Minigin/InputManager.h"
#include <string>
#include "HighscoreParser.h"
#include "../Minigin/EventQueue.h"

namespace dae
{
	class GameObject;
}
namespace pacman
{
	class GamestateManager;
	class GameState
	{
	public:
		explicit GameState();
		virtual ~GameState() = default;
		GameState(const GameState& other) = delete;
		GameState(GameState&& other) = delete;
		GameState& operator=(const GameState& other) = delete;
		GameState& operator=(GameState&& other) = delete;
		virtual void OnEnter();
		virtual std::unique_ptr<pacman::GameState> Notify(const dae::Event&);
		virtual void OnExit();
	protected:
		GamestateManager* m_gamestateManager;
	};

	class NameSelectState final : public GameState
	{
	public:
		void OnEnter();
		std::unique_ptr<pacman::GameState> Notify(const dae::Event& event);
		void OnExit();
	private:
		int m_nrSelectedNames{};
		const int m_maxNrPlayers{ 2 };
		dae::InputManager& m_inputManager{ dae::InputManager::GetInstance() };
	};

	class MainMenuState final : public GameState
	{
	public:
		void OnEnter();
		std::unique_ptr<pacman::GameState> Notify(const dae::Event& event);
		void OnExit();

	private:
		dae::InputManager& m_inputManager{ dae::InputManager::GetInstance() };
		dae::EventQueue& m_eventQueue{ dae::EventQueue::GetInstance() };
	};

	class PlayState : public GameState
	{
	public:
		explicit PlayState(int nrPacman);
		virtual ~PlayState() = default;
		PlayState(const PlayState& other) = delete;
		PlayState(PlayState&& other) = delete;
		PlayState& operator=(const PlayState& other) = delete;
		PlayState& operator=(PlayState&& other) = delete;

		virtual void OnEnter() override;
		virtual std::unique_ptr<pacman::GameState> Notify(const dae::Event&) override;
		virtual void OnExit() override;
	protected:
		int m_nrEatenPellets{};
		int m_totalNrPellets{};
		int m_nrPacman{ 1 };
		int m_nrDeaths{};
		int m_levelIdx{ 0 };
		std::vector<std::string> m_levels{ "Level_one", "Level_two", "Level_three" };
		dae::InputManager& m_inputManager{ dae::InputManager::GetInstance() };

		virtual void LoadScene() = 0;
	private:
		std::unique_ptr<pacman::GameState> NextLevel();
	};

	class SingleplayerState final : public PlayState
	{
	public:
		SingleplayerState(int nrPacman);
	private:
		void LoadScene();
	};

	class CoopState final : public PlayState
	{
	public:
		CoopState(int nrPacman);
	private:
		void LoadScene();
	};

	class VersusState final : public PlayState
	{
	public:
		VersusState(int nrPacman);
	private:
		void LoadScene();
	};

	class EndState final : public GameState
	{
	public:
		void OnEnter();
		std::unique_ptr<pacman::GameState> Notify(const dae::Event& event);
		void OnExit();
	private:
		HighscoreParser m_highscoreParser{};
	};
}