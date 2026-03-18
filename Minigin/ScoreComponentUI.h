#pragma once
#include "Component.h"
#include "Observer.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
#include <string>

#ifdef USE_STEAMWORKS
#include <steam_api.h>
#endif

namespace dae
{
	class ScoreComponentUI : public Component, public Observer
	{
	public:
		ScoreComponentUI(GameObject* owner) :
			Component(owner)
		{
			m_textComponent = owner->GetComponent<TextComponent>();
		}

		virtual void Notify(GameObject* gameObject, Event event) override
		{
			switch (event)
			{
			case dae::Event::ADD_SCORE:
			{
				int score{ gameObject->GetComponent<ScoreComponent>()->GetScore() };
				m_textComponent->SetText("Score: " + std::to_string(score));
				break;
			}
			case dae::Event::GAME_WON:
				UnlockSteamAchievement("ACH_WIN_ONE_GAME");
				break;
			}
		}
		

	private:
		TextComponent* m_textComponent;

		void UnlockSteamAchievement(const char* achievementID)
		{
			if (!SteamUserStats()) return;
			SteamUserStats()->SetAchievement(achievementID);
			SteamUserStats()->StoreStats();
		}
	};
}