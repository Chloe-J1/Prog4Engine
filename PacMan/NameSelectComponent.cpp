#include "NameSelectComponent.h"
#include "LetterSelectComponent.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "Events.h"
#include "../Minigin/GameObject.h"
#include <iostream>

pacman::NameSelectComponent::NameSelectComponent(dae::GameObject* owner, dae::GameObject* button):
	Component(owner),
	m_button{button}
{
	dae::EventQueue::GetInstance().AddEventHandler(this);
}

pacman::NameSelectComponent::~NameSelectComponent()
{
	dae::EventQueue::GetInstance().RemoveEventHandler(this);
}


void pacman::NameSelectComponent::Notify(const dae::Event& event)
{
	if (event.id == "BUTTON_PRESSED")
	{
		auto* arg = static_cast<SenderArg*>(event.arg.get());
		dae::GameObject* sender{ arg->sender };
		if (sender != m_button) return;
		std::string name{};
		for (const auto& letter : m_letters)
		{
			name += letter->GetLetter();
		}
		SavePlayerName(name);

		dae::Event e{ "NAME_SELECTED" };
		m_eventQueue.Invoke(std::move(e));
	}
}

void pacman::NameSelectComponent::AddLetterComp(LetterSelectComponent* letterComp)
{
	m_letters.push_back(letterComp);
}

void pacman::NameSelectComponent::SavePlayerName(const std::string& name)
{
	std::filesystem::path filepath = std::filesystem::path(DATA_PATH) / "Scores.json";
	std::ifstream iFile(filepath);

	nlohmann::json data;
	try
	{
		data = nlohmann::json::parse(iFile);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		std::cerr << "JSON parse error in " << filepath << ": " << e.what() << "\n";
		return;
	}

	iFile.close();

	data["CurrentPlayers"].push_back({
		{"name", name},
		{"score", 0}
	});

	std::ofstream oFile(filepath);
	oFile << data.dump(4);
	oFile.close();
}