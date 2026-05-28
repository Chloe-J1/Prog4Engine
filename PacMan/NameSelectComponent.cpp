#include "NameSelectComponent.h"
#include "ButtonComponent.h"
#include "LetterSelectComponent.h"
#include <nlohmann/json.hpp>
#include <fstream>

pacman::NameSelectComponent::NameSelectComponent(dae::GameObject* owner):
	Component(owner)
{
	m_eventQueue.AddObserver(this);
}

pacman::NameSelectComponent::~NameSelectComponent()
{
	m_eventQueue.RemoveObserver(this);
}

void pacman::NameSelectComponent::Notify(dae::GameObject* sender, const dae::Event& event)
{
	if (event.id == "BUTTON_PRESSED")
	{
		ButtonComponent* button{ sender->GetComponent<ButtonComponent>() };

		if (button->GetName() == "SelectName")
		{
			std::string name{};
			for (const auto& letter : m_letters)
			{
				name += letter->GetLetter();
			}
			SavePlayerName(name);

			dae::Event e{ "NAME_SELECTED" };
			m_eventQueue.Invoke(std::move(e), GetGameObject());
		}
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

	nlohmann::json data = nlohmann::json::parse(iFile);

	iFile.close();

	data["CurrentPlayers"].push_back({
		{"name", name},
		{"score", 0}
		});

	std::ofstream oFile(filepath);
	oFile << data.dump(4);
}