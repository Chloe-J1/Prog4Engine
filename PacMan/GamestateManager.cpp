#include "GamestateManager.h"
#include "../Minigin/EventQueue.h"
#include "Commands.h"
#include <memory>
#include "GameState.h"
#include <InputData.h>

pacman::GamestateManager::GamestateManager()
{
	dae::EventQueue::GetInstance().AddEventHandler(this);
	m_inputManager.BindCommand(SDL_SCANCODE_F2, dae::TriggerEvent::PressedThisFrame, std::make_unique<ToggleSound>());
}

pacman::GamestateManager::~GamestateManager()
{
	dae::EventQueue::GetInstance().RemoveEventHandler(this);
	m_inputManager.UnbindCommand(SDL_SCANCODE_F2, dae::TriggerEvent::PressedThisFrame);
}

void pacman::GamestateManager::Init()
{
	m_gameState = std::make_unique<NameSelectState>();
	m_gameState->OnEnter();
}

void pacman::GamestateManager::SetTotalPellets(int value)
{
	m_totalPellets = value;
}

int pacman::GamestateManager::GetTotalPellets() const
{
	return m_totalPellets;
}

void pacman::GamestateManager::Notify(const dae::Event& event)
{
	auto newState{ m_gameState->Notify(event) };
	if (newState != nullptr)
	{
		m_gameState->OnExit();
		m_gameState = std::move(newState);
		m_gameState->OnEnter();
	}
}

void pacman::GamestateManager::SetSoloButton(dae::GameObject* btn)
{
	m_soloButton = btn;
}

void pacman::GamestateManager::SetCoopButton(dae::GameObject* btn)
{
	m_coopButton = btn;
}

void pacman::GamestateManager::SetVersusButton(dae::GameObject* btn)
{
	m_versusButton = btn;
}

void pacman::GamestateManager::SetHomeButton(dae::GameObject* btn)
{
	m_homeButton = btn;
}

dae::GameObject* pacman::GamestateManager::GetSoloButton() const
{
	return m_soloButton;
}

dae::GameObject* pacman::GamestateManager::GetCoopButton() const
{
	return m_coopButton;
}

dae::GameObject* pacman::GamestateManager::GetVersusButton() const
{
	return m_versusButton;
}

dae::GameObject* pacman::GamestateManager::GetHomeButton() const
{
	return m_homeButton;
}

void pacman::GamestateManager::ClearButtons()
{
	m_soloButton = nullptr;
	m_coopButton = nullptr;
	m_versusButton = nullptr;
	m_homeButton = nullptr;
}
