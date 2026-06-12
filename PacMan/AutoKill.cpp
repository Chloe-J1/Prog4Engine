#include "AutoKill.h"
#include "../Minigin/GameObject.h"

pacman::AutoKill::AutoKill(dae::GameObject* owner, float sec) :
	Component(owner),
	m_maxTime{sec}
{}

void pacman::AutoKill::Update(float elapsedSec)
{
	m_timer += elapsedSec;
	if (m_timer >= m_maxTime)
	{
		GetGameObject()->SetIsAlive(false);
	}
}

