#pragma once
#include "Component.h"
namespace pacman
{
	class BasePellet : public dae::Component
	{
	public:
		BasePellet(dae::GameObject* owner):
			Component(owner)
		{};
		int GetValue() { return m_value; }
	protected:
		int m_value{ 0 };
	};

	class SmallPellet final : public BasePellet
	{
	public:
		SmallPellet(dae::GameObject* owner) :
			BasePellet(owner)
		{
			m_value = 10;
		}
	};

	class PowerPellet final : public BasePellet
	{
	public:
		PowerPellet(dae::GameObject* owner) :
			BasePellet(owner)
		{
			m_value = 50;
		}
	};
}