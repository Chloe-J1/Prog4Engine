#pragma once
#include "Component.h"
namespace dae
{
	class BasePellet : public Component
	{
	public:
		BasePellet(GameObject* owner):
			Component(owner)
		{};
		int GetValue() { return m_value; }
	protected:
		int m_value{ 0 };
	};

	class SmallPellet final : public BasePellet
	{
	public:
		SmallPellet(GameObject* owner) :
			BasePellet(owner)
		{
			m_value = 10;
		}
	};

	class PowerPellet final : public BasePellet
	{
	public:
		PowerPellet(GameObject* owner) :
			BasePellet(owner)
		{
			m_value = 50;
		}
	};
}