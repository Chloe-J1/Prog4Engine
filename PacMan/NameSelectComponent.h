#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/Observer.h"
#include <vector>
#include "../Minigin/EventQueue.h"

namespace pacman
{
	class LetterSelectComponent;
	class NameSelectComponent final : public dae::Component, public dae::Observer
	{
	public:
		NameSelectComponent(dae::GameObject* owner, dae::GameObject* button );
		~NameSelectComponent();
		NameSelectComponent(const NameSelectComponent& other) = delete;
		NameSelectComponent(NameSelectComponent&& other) = delete;
		NameSelectComponent& operator=(const NameSelectComponent& other) = delete;
		NameSelectComponent& operator=(NameSelectComponent&& other) = delete;

		void Notify(dae::GameObject* sender, const dae:: Event& event);
		void AddLetterComp(LetterSelectComponent* letterComp);
	private:
		std::vector<LetterSelectComponent*> m_letters{};
		dae::EventQueue& m_eventQueue{ dae::EventQueue::GetInstance() };
		dae::GameObject* m_button;

		void SavePlayerName(const std::string& name);
	};
}