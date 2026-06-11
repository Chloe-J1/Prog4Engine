#pragma once
#include "Component.h"
namespace pacman
{
	class BasePellet : public dae::Component
	{
	public:
		explicit BasePellet(dae::GameObject* owner);
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
		explicit SmallPellet(dae::GameObject* owner);
	};

	class PowerPellet final : public BasePellet
	{
	public:
		explicit PowerPellet(dae::GameObject* owner);
	};
}