#include "Pellets.h"

pacman::BasePellet::BasePellet(dae::GameObject* owner) :
	Component(owner)
{
}
int pacman::BasePellet::GetValue()
{
	return m_value;
}
;

pacman::SmallPellet::SmallPellet(dae::GameObject* owner) :
	BasePellet(owner)
{
	m_value = 10;
}

pacman::PowerPellet::PowerPellet(dae::GameObject* owner) :
	BasePellet(owner)
{
	m_value = 50;
}