#pragma once
#include "Component.h"
namespace pacman
{
	class BasePellet : public dae::Component
	{
	public:
		BasePellet(dae::GameObject* owner);
		int GetValue();
	protected:
		int m_value{ 0 };
	};

	class SmallPellet final : public BasePellet
	{
	public:
		SmallPellet(dae::GameObject* owner);
	};

	class PowerPellet final : public BasePellet
	{
	public:
		PowerPellet(dae::GameObject* owner);
	};
}