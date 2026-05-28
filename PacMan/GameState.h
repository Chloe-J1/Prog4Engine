#pragma once
#include <memory>
#include "../Minigin/Event.h"
#include <vector>
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
		std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event);
	private:
		int m_nrSelectedNames{};
		const int m_maxNrPlayers{ 2 };
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
		virtual ~PlayState() = default;
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
	private:
		void LoadScene();
	};

	class CoopState final : public PlayState
	{
	protected:
		int m_nrPacman{ 2 };
	private:
		void LoadScene();
	};

	class VersusState final : public PlayState
	{
	private:
		void LoadScene();
	};

	class WinState final : public GameState
	{
	public:
		void OnEnter();
		std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event);
	};

	class LoseState final : public GameState
	{
	public:
		void OnEnter();
		std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event);
	};
}