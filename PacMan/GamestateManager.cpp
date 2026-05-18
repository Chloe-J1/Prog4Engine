#include "GamestateManager.h"
#include "../Minigin/EventQueue.h"

pacman::GamestateManager::GamestateManager()
{
	dae::EventQueue::GetInstance().AddObserver(this);
}

pacman::GamestateManager::~GamestateManager()
{
	dae::EventQueue::GetInstance().RemoveObserver(this);
}

void pacman::GamestateManager::Init()
{
	m_gameState = std::make_unique<MainMenuState>();
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

void pacman::GamestateManager::Notify(dae::GameObject* sender, const dae::Event& event)
{
	auto newState{ m_gameState->Notify(sender, event) };
	if (newState != nullptr)
	{
		m_gameState->OnExit();
		m_gameState = std::move(newState);
		m_gameState->OnEnter();
	}
}
