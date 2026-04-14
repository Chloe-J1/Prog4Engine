#pragma once
#include <glm/glm.hpp>
#include "../PacMan/PlayerMovement.h"
#include "../Minigin/Command.h"	
namespace pacman
{
	// MOVE
	//********
	class Move final : public dae::GameObjectCommand
	{
	public:
		Move(dae::GameObject* gameObject, const glm::vec2& direction) :
			GameObjectCommand(gameObject),
			m_direction{direction}
		{
			m_moveComp = GetGameObject()->GetComponent<pacman::PlayerMovement>();
		}
		virtual void Execute() override;
		
	private:
		glm::vec2 m_direction;
		pacman::PlayerMovement* m_moveComp;
	};

}
