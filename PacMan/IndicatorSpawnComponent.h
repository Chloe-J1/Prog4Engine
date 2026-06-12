#pragma once
#include "../Minigin/Component.h"
#include <glm/fwd.hpp>
#include <memory>
#include "../Minigin/Scene.h"
#include "../Minigin/SceneManager.h"
#include "../Minigin/IEventHandler.h"

namespace pacman
{
	class IndicatorSpawnComponent final : public dae::Component, public dae::IEventHandler
	{
	public:
		explicit IndicatorSpawnComponent(dae::GameObject* owner);
		~IndicatorSpawnComponent();
		IndicatorSpawnComponent(const IndicatorSpawnComponent& other) = delete;
		IndicatorSpawnComponent(Component&& other) = delete;
		IndicatorSpawnComponent& operator=(const IndicatorSpawnComponent& other) = delete;
		IndicatorSpawnComponent& operator=(IndicatorSpawnComponent&& other) = delete;
		void Notify(const dae::Event& event);
	private:
		std::unique_ptr<dae::GameObject> CreateIndicator(const glm::vec2& spawnPos, int value);
		dae::Scene& m_scene{ dae::SceneManager::GetInstance().GetActiveScene() };
	};
}