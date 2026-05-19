#pragma once
#include <memory>
#include "../Minigin/Event.h"
namespace dae
{
	class GameObject;
}
namespace pacman
{
	class GameState
	{
	public:
		virtual ~GameState() {};
		virtual void OnEnter() {};
		virtual std::unique_ptr<pacman::GameState> Notify(dae::GameObject*, const dae::Event&) { return nullptr; };
		virtual void OnExit() {};
	};

	class MainMenuState final : public GameState
	{
	public:
		virtual void OnEnter() override;
		virtual std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event) override;
	};

	class PlayState final : public GameState
	{
	public:
		virtual void OnEnter() override;
		virtual std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event) override;

	private:
		int m_nrEatenPellets{};
		int m_totalNrPellets{};
	};

	class WinState final : public GameState
	{
	public:
		virtual void OnEnter() override;
		virtual std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event) override;
	};

	class LoseState final : public GameState
	{
	public:
		virtual void OnEnter() override;
	};
}