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

	class LoadingState final : public GameState
	{
	public:
		virtual void OnEnter() override;
	};

	class MainMenuState final : public GameState
	{
	public:
		virtual void OnEnter() override;
		virtual std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event);
	};

	class PlayState final : public GameState
	{
	public:
		virtual void OnEnter() override;
		virtual std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event);

	private:
		int m_nrEatenPellets{};
		int m_totalNrPellets{};
	};

	class WinState final : public GameState
	{
	public:
		virtual void OnEnter() override;
		virtual std::unique_ptr<pacman::GameState> Notify(dae::GameObject* sender, const dae::Event& event);
	};

	class LoseState final : public GameState
	{
	public:
		virtual void OnEnter() override;
	};
}