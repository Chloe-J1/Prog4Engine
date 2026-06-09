#pragma once
#include "../Minigin/Component.h"
#include <glm/glm.hpp>
#include "../Minigin/IObserver.h"

namespace pacman
{
	class RespawnComponent final : public dae::Component, public dae::IObserver
	{
	public:
		RespawnComponent(dae::GameObject* owner, const glm::vec2& respawnPos);
		~RespawnComponent();
		RespawnComponent(const RespawnComponent& other) = delete;
		RespawnComponent(RespawnComponent&& other) = delete;
		RespawnComponent& operator=(const RespawnComponent& other) = delete;
		RespawnComponent& operator=(RespawnComponent&& other) = delete;

		void Notify(dae::GameObject* sender, const dae::Event& event);
	private:
		glm::vec2 m_respawnPos;
	};
}