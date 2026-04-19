#pragma once
#include "../Minigin/Singleton.h"
#include "../Minigin/Observer.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/SceneManager.h"
#include "../Minigin/RenderComponent.h"
#include "../Minigin/ResourceManager.h"
#include "../Minigin/TextComponent.h"
#include "../Minigin/InputManager.h"
#include "../Minigin/WindowConfig.h"


#include "Commands.h"
#include "PlayerMovement.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "Commands.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "HealthComponentUI.h"
#include "Subject.h"
#include "ScoreComponent.h"
#include "ScoreComponentUI.h"
#include "Hitbox.h"
#include "Ghost.h"
#include "PlayerAnimator.h"
#include "ButtonComponent.h"
#include "Events.h"
#include "ButtonAnimator.h"

#include <fstream>
#include <sstream>
namespace pacman
{
	inline std::unique_ptr<dae::GameObject> CreateWall(float x, float y)
	{
		std::unique_ptr<dae::GameObject> wall = std::make_unique <dae::GameObject>();
		wall->AddComponent<dae::RenderComponent>("Wall_24.png");
		wall->AddComponent<dae::Hitbox>(24, 24);
		wall->SetLocalPosition(x, y);
		wall->SetLayer("Obstacle");
		return wall;
	}
	inline std::unique_ptr<dae::GameObject> CreatePellet(float x, float y)
	{
		const int offset{ 10 };
		std::unique_ptr<dae::GameObject> pellet = std::make_unique<dae::GameObject>();
		pellet->AddComponent<dae::Hitbox>(4, 4);
		pellet->AddComponent<dae::RenderComponent>("Pellet_small.png");
		pellet->AddComponent<pacman::SmallPellet>();
		pellet->SetLocalPosition(x + offset, y + offset);
		return pellet;
	}


	class GamestateManager final : public dae::Singleton<GamestateManager>, public dae::Observer
	{
	public:
		virtual void Notify(dae::GameObject*, const dae::Event&) override
		{
			/*if (event.id == "PLAYER_DIED")
			{
				LoseScene();
			}*/
		}
		void MapScene()
		{
			dae::SceneManager::GetInstance().CreateScene("mapScene");
			dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();

			// TODO: Wrapper class for map loading
			std::string filename{ "Data/Maps/Level_one.txt" };
			std::ifstream iFile;
			iFile.open(filename);
			std::string line;
			float x{};
			float y{};
			float size{ 24.f };
						
			if (iFile.is_open())
			{
				while (std::getline(iFile, line))
				{
					std::stringstream ss(line);
					std::string type;
					
					while (std::getline(ss, type, ','))
					{
						if (type == "w")
						{
							scene.Add(CreateWall(x, y));
						}
						else if (type == "p")
						{
							scene.Add(CreatePellet(x, y));
						}
						x += size;
					}
					y += size;
					x = 0;
				}
				iFile.close();
			}
			else
			{
				throw std::invalid_argument("this file can't be opened");
			}

			std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
			go->AddComponent<dae::RenderComponent>("Pacman.png");
			go->AddComponent<dae::SpriteComponent>(3, 1, 0.2f);
			go->AddComponent<dae::Hitbox>(16, 16);
			go->AddComponent<pacman::PlayerMovement>(true, false);
			go->SetLocalPosition(28, 28);



			scene.Add(std::move(go));
		}
		void OtherScene()
		{
			dae::SceneManager::GetInstance().CreateScene("otherScene");
			//dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();
		}
		void GameScene()
		{
			dae::SceneManager::GetInstance().CreateScene("gameScene");
			dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();


			// FPS
			std::unique_ptr<dae::GameObject> fpsgo = std::make_unique<dae::GameObject>();
			fpsgo->SetLocalPosition(20, 20);
			fpsgo->AddComponent<dae::RenderComponent>();
			auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
			fpsgo->AddComponent<dae::TextComponent>("FPS: ", font);
			fpsgo->AddComponent<pacman::FPSComponent>();

			scene.Add(std::move(fpsgo));



			// Score UI -> MRS PACMAN
			std::unique_ptr<dae::GameObject> scoreGo = std::make_unique<dae::GameObject>();
			scoreGo->AddComponent<dae::RenderComponent>();
			font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
			scoreGo->AddComponent<dae::TextComponent>("Score: 0", font);
			scoreGo->AddComponent<pacman::ScoreComponentUI>();

			scoreGo->SetLocalPosition(670, 10);
			// MrsPacman
			//**********
			std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
			go->AddComponent<dae::RenderComponent>("MrsPacman.png");
			go->AddComponent<dae::SpriteComponent>(3, 4, 0.2f);
			go->AddComponent<pacman::PlayerAnimator>(go->GetComponent<dae::SpriteComponent>());
			go->AddComponent<dae::Hitbox>(16, 16);
			go->AddComponent<pacman::ScoreComponent>();
			// add observer
			go->GetComponent<pacman::ScoreComponent>()->GetSubject()->AddObserver(
				scoreGo->GetComponent<pacman::ScoreComponentUI>()
			);

			go->AddComponent<pacman::PlayerMovement>(true, true, 0);
			go->SetLocalPosition(200, 200);

			scene.Add(std::move(scoreGo));


			// Health UI
			std::unique_ptr<dae::GameObject> healthUIGo = std::make_unique<dae::GameObject>();
			healthUIGo->AddComponent<dae::RenderComponent>("Health.png");
			healthUIGo->AddComponent<dae::SpriteComponent>(1, 4, 0.f);
			healthUIGo->AddComponent<pacman::HealthComponentUI>();
			go->AddComponent<pacman::HealthComponent>();
			// add health observer
			go->GetComponent<pacman::HealthComponent>()->GetTakeDamageEvent()->AddObserver(
				healthUIGo->GetComponent<pacman::HealthComponentUI>()
			);
			go->GetComponent<pacman::HealthComponent>()->GetTakeDamageEvent()->AddObserver(
				&pacman::GamestateManager::GetInstance()
			);

			healthUIGo->SetLocalPosition(480, 540);

			std::unique_ptr<dae::GameObject> goHealthTextF = std::make_unique<dae::GameObject>();
			goHealthTextF->SetParent(healthUIGo.get(), false);

			goHealthTextF->AddComponent<dae::RenderComponent>();
			font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
			goHealthTextF->AddComponent<dae::TextComponent>("Health:", font);

			goHealthTextF->SetLocalPosition(-55.f, -3);
			scene.Add(std::move(goHealthTextF));
			scene.Add(std::move(healthUIGo));

			


			scene.Add(std::move(go));




			// Pacman
			//*********

			go = std::make_unique<dae::GameObject>();
			go->AddComponent<dae::RenderComponent>("Pacman.png");
			go->AddComponent<dae::SpriteComponent>(3, 4, 0.2f);
			go->AddComponent<pacman::PlayerAnimator>(go->GetComponent<dae::SpriteComponent>());
			go->AddComponent<dae::Hitbox>(16, 16);
			// Health UI
			healthUIGo = std::make_unique<dae::GameObject>();
			healthUIGo->AddComponent<dae::RenderComponent>("Health.png");
			healthUIGo->AddComponent<dae::SpriteComponent>(1, 4, 0.f);
			healthUIGo->AddComponent<pacman::HealthComponentUI>();


			healthUIGo->SetLocalPosition(480, 555);

			std::unique_ptr<dae::GameObject> goText = std::make_unique<dae::GameObject>();
			goText->SetParent(healthUIGo.get(), false);

			goText->AddComponent<dae::RenderComponent>();
			font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
			goText->AddComponent<dae::TextComponent>("Health:", font);

			goText->SetLocalPosition(-55.f, -3);
			scene.Add(std::move(goText));
			go->AddComponent<pacman::HealthComponent>();
			// add health observer
			go->GetComponent<pacman::HealthComponent>()->GetTakeDamageEvent()->AddObserver(
				healthUIGo->GetComponent<pacman::HealthComponentUI>()
			);
			scoreGo = std::make_unique<dae::GameObject>();
			scoreGo->AddComponent<dae::RenderComponent>(); 
			font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
			scoreGo->AddComponent<dae::TextComponent>("Score: 0", font);
			scoreGo->AddComponent<pacman::ScoreComponentUI>();

			scoreGo->SetLocalPosition(670, 30);

			// add score observer
			go->AddComponent<pacman::ScoreComponent>();
			go->GetComponent<pacman::ScoreComponent>()->GetSubject()->AddObserver(
				scoreGo->GetComponent<pacman::ScoreComponentUI>()
			);


			go->SetLocalPosition(100, 100);

			go->AddComponent<pacman::PlayerMovement>(false, true, 1);

			scene.Add(std::move(healthUIGo));
			scene.Add(std::move(scoreGo));
			scene.Add(std::move(go));

			// Explanation
			std::unique_ptr<dae::GameObject> expl = std::make_unique<dae::GameObject>();
			expl->AddComponent<dae::RenderComponent>();
			expl->AddComponent<dae::TextComponent>("Use D-pad to move players     Use A to lose lives     Use B to gain points", font);
			scene.Add(std::move(expl));


			// Pellet
			std::unique_ptr<dae::GameObject> pellet = std::make_unique<dae::GameObject>();
			pellet->AddComponent<dae::Hitbox>(4, 4);
			pellet->AddComponent<dae::RenderComponent>("Pellet_small.png");
			pellet->AddComponent<pacman::SmallPellet>();
			pellet->SetLocalPosition(500, 202);

			scene.Add(std::move(pellet));

			std::unique_ptr<dae::GameObject> bigpellet = std::make_unique<dae::GameObject>();
			bigpellet->AddComponent<dae::Hitbox>(8, 8);
			bigpellet->AddComponent<dae::RenderComponent>("Pellet_big.png");
			bigpellet->AddComponent<pacman::PowerPellet>();
			bigpellet->SetLocalPosition(500, 212);

			scene.Add(std::move(bigpellet));

			// Ghost
			std::unique_ptr<dae::GameObject> ghost = std::make_unique<dae::GameObject>();
			ghost->AddComponent<dae::Hitbox>(16, 16);
			ghost->AddComponent<dae::RenderComponent>("Ghost_red.png");
			ghost->AddComponent<dae::SpriteComponent>(1, 6);
			ghost->AddComponent<pacman::GhostComponent>();
			ghost->SetLocalPosition(300, 300);
			scene.Add(std::move(ghost));

			// Wall
			scene.Add(CreateWall(250, 300));

		}

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

		void MenuScene()
		{
			const int wWidth{ dae::WindowConfig::GetInstance().GetWidth() };
			const int wHeight{ dae::WindowConfig::GetInstance().GetHeight() };


			dae::SceneManager::GetInstance().CreateScene("menuScene");
			dae::Scene& scene = dae::SceneManager::GetInstance().GetActiveScene();

			// Bind MenuManager commands
			dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_T, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PreviousButton>());
			dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_Y, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::NextButton>());

			// Button animator - used for all buttons
			std::unique_ptr<dae::GameObject> buttonAnim = std::make_unique<dae::GameObject>();
			buttonAnim->AddComponent<pacman::ButtonAnimator>();
			scene.Add(std::move(buttonAnim));

			// Game Button
			std::unique_ptr<dae::GameObject> go = std::make_unique<dae::GameObject>();
			go->AddComponent<dae::RenderComponent>("Button.png");
			go->AddComponent<dae::SpriteComponent>(1, 2);
			go->AddComponent<ButtonComponent>("LoadGameScene");

			dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_SPACE, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PressButton>(go.get()));

			go->SetLocalPosition(float(wWidth - 72 / 2) / 2.f, float(wHeight - 24 / 2) / 2.f);

				// Explanation
				std::unique_ptr<dae::GameObject> expl = std::make_unique<dae::GameObject>();
				expl->AddComponent<dae::RenderComponent>();
				auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
				expl->AddComponent<dae::TextComponent>("Game", font);
				expl->SetParent(go.get(), false);
				expl->SetLocalPosition(10, 3);
				
			scene.Add(std::move(go));
			scene.Add(std::move(expl));

			// Test Button
			go = std::make_unique<dae::GameObject>();
			go->AddComponent<dae::RenderComponent>("Button.png");
			go->AddComponent<dae::SpriteComponent>(1, 2);
			go->AddComponent<ButtonComponent>("LoadLoseScene");

			dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_SPACE, dae::TriggerEvent::PressedThisFrame, std::make_unique<pacman::PressButton>(go.get()));

			go->SetLocalPosition(float(wWidth - 72 / 2) / 2.f, float(wHeight - 24 / 2 + 60) / 2.f);

				// Explanation
				expl = std::make_unique<dae::GameObject>();
				expl->AddComponent<dae::RenderComponent>();
				font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 17);
				expl->AddComponent<dae::TextComponent>("Test", font);
				expl->SetParent(go.get(), false);
				expl->SetLocalPosition(10, 3);

			scene.Add(std::move(go));
			scene.Add(std::move(expl));

		}
	private:
		

	};
}