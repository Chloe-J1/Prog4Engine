#pragma once
#include <glm/glm.hpp>
#include "../PacMan/PlayerMovement.h"
#include "../Minigin/Command.h"	


#include <iostream>
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

	// BUTTON SELECTION
	//********
	class NextButton final : public dae::Command
	{
	public:
		virtual void Execute() override;
	};

	class PreviousButton final : public dae::Command
	{
	public:
		virtual void Execute() override;
	};

	// TEST
	class GameScene final : public dae::GameObjectCommand
	{
	public:
		GameScene(dae::GameObject* gameObject) :
			GameObjectCommand(gameObject)
		{
		}
		virtual void Execute() override;
	};

	class LoseScene final : public dae::GameObjectCommand
	{
	public:
		LoseScene(dae::GameObject* gameObject) :
			GameObjectCommand(gameObject)
		{
		}
		virtual void Execute() override;
	};
}
