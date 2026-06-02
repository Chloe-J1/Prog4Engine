#pragma once
#include "Component.h"
#include <iostream>
namespace pacman
{
	class BasePellet : public dae::Component
	{
	public:
		BasePellet(dae::GameObject* owner);
		virtual ~BasePellet() = default;
		BasePellet(const BasePellet& other) = delete;
		BasePellet(BasePellet&& other) = delete;
		BasePellet& operator=(const BasePellet& other) = delete;
		BasePellet& operator=(BasePellet&& other) = delete;
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