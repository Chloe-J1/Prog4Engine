#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/EventQueue.h"
#include <vector>
#include <string>

namespace pacman
{
	class LetterSelectComponent;
	class NameSelectComponent final : public dae::Component
	{
	public:
		NameSelectComponent(dae::GameObject* owner, dae::GameObject* button );

		void AddLetterComp(LetterSelectComponent* letterComp);
	private:
		std::vector<LetterSelectComponent*> m_letters{};
		dae::EventQueue& m_eventQueue{ dae::EventQueue::GetInstance() };

		void SavePlayerName(const std::string& name);
	};
}