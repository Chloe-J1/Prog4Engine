#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/Observer.h"
namespace dae
{
	class EventQueue;
}

namespace pacman
{
	class EatenComponent final : public dae::Component, public dae::Observer
	{
	public:
		EatenComponent(dae::GameObject* owner);
		~EatenComponent();
		EatenComponent(const EatenComponent& other) = delete;
		EatenComponent(EatenComponent&& other) = delete;
		EatenComponent& operator=(const EatenComponent& other) = delete;
		EatenComponent& operator=(EatenComponent&& other) = delete;

		virtual void Notify(dae::GameObject* sender, const dae::Event& event) override;
	private:
		virtual void OnCollision(dae::GameObject* other) override;
		bool m_isVulnerable{ false };
		dae::EventQueue* m_eventQueue{};
	};
}