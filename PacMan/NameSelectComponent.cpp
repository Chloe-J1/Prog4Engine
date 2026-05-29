#include "NameSelectComponent.h"
#include "ButtonComponent.h"
#include "LetterSelectComponent.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "../Minigin/GameObject.h"

pacman::NameSelectComponent::NameSelectComponent(dae::GameObject* owner, dae::GameObject* button):
	Component(owner)
{
	ButtonComponent* buttoncomp{ button->GetComponent<ButtonComponent>()};
	buttoncomp->OnClick([&]() {
			std::string name{};
			for (const auto& letter : m_letters)
			{
				name += letter->GetLetter();
			}
			SavePlayerName(name);

			dae::Event e{ "NAME_SELECTED" };
			m_eventQueue.Invoke(std::move(e), GetGameObject());
		});
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
		{"name", name}
	});

	std::ofstream oFile(filepath);
	oFile << data.dump(4);
	oFile.close();
}