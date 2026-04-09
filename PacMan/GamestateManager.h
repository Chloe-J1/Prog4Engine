#pragma once
#include "../Minigin/Singleton.h"
#include "../Minigin/Observer.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/Event.h"
#include "../Minigin/SceneManager.h"
#include "../Minigin/RenderComponent.h"
#include "../Minigin/ResourceManager.h"
#include "../Minigin/TextComponent.h"
namespace pacman
{
	class GamestateManager final : public dae::Singleton<GamestateManager>, public dae::Observer
	{
	public:
		virtual void Notify(dae::GameObject*, const Event& event) override
		{
			if (event.id == EventId::PLAYER_DIED)
			{
				LoseScene();
			}
		}
	private:
		void LoseScene()
		{
			dae::SceneManager::GetInstance().CreateScene("loseScene");
			dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();
			std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
			go->AddComponent<dae::RenderComponent>();
			auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
			go->AddComponent<dae::TextComponent>("GAME OVER", font);

			scene.Add(std::move(go));
		}
	};
}