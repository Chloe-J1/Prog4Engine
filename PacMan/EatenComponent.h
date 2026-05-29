#pragma once
#include "../Minigin/Component.h"
namespace dae
{
	class EventQueue;
}

namespace pacman
{
	class EatenComponent final : public dae::Component
	{
	public:
		EatenComponent(dae::GameObject* owner);

		void SetVulnerable(bool isVulnerable);
	private:
		virtual void OnCollision(dae::GameObject* other) override;
		bool m_isVulnerable{ false };
		dae::EventQueue* m_eventQueue{};
	};
}