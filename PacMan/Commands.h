#pragma once
#include <glm/glm.hpp>
#include "../PacMan/PlayerMovement.h"
#include "../Minigin/Command.h"	
#include <string>


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

	class PressButton final : public dae::GameObjectCommand
	{
	public:
		PressButton(dae::GameObject* gameObject):
			GameObjectCommand(gameObject)
		{ }

		virtual void Execute() override;
	};
}
