#pragma once
#include <memory>
#include "../Minigin/Event.h"
#include "../Minigin/InputManager.h"
#include <string>

namespace dae
{
	class GameObject;
}
namespace pacman
{
	class GameState
	{
	public:
		virtual ~GameState() = default;
		virtual void OnEnter();
		virtual std::unique_ptr<pacman::GameState> Notify(dae::GameObject*, const dae::Event&) { return nullptr; };
		virtual void OnExit();
	};

	class NameSelectState final : public GameState
	{
	public:
		void OnEnter();
		std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event);
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
		std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event);
	};

	class PlayState : public GameState
	{
	public:
		PlayState(int nrPacman);
		virtual ~PlayState() = default;
		PlayState(const PlayState& other) = delete;
		PlayState(PlayState&& other) = delete;
		PlayState& operator=(const PlayState& other) = delete;
		PlayState& operator=(PlayState&& other) = delete;

		virtual void OnEnter();
		virtual std::unique_ptr<pacman::GameState> Notify(dae::GameObject*, const dae::Event&);
	protected:
		int m_nrEatenPellets{};
		int m_totalNrPellets{};
		int m_nrPacman{ 1 };
		int m_nrDeaths{};
		int m_levelIdx{ 0 };
		std::vector<std::string> m_levels{ "Level_one", "Level_two", "Level_three" };

		virtual void LoadScene() = 0;
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
		std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event);
	};
}