#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/EventQueue.h"
#include "../Minigin/IObserver.h"
#include <vector>
#include <string>

namespace pacman
{
	class LetterSelectComponent;
	class NameSelectComponent final : public dae::Component, public dae::IObserver
	{
	public:
		NameSelectComponent(dae::GameObject* owner, dae::GameObject* button );
		~NameSelectComponent();

		void Notify(dae::GameObject* sender, const dae::Event& event);
		void AddLetterComp(LetterSelectComponent* letterComp);
	private:
		std::vector<LetterSelectComponent*> m_letters{};
		dae::EventQueue& m_eventQueue{ dae::EventQueue::GetInstance() };
		dae::GameObject* m_button;

		void SavePlayerName(const std::string& name);
	};
}