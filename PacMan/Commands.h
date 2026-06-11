#pragma once
#include <glm/glm.hpp>
#include "../PacMan/PlayerMovement.h"
#include "../Minigin/Command.h"	
#include "../Minigin/EventQueue.h"
#include "SoundManager.h"

namespace pacman
{
	// MOVE
	//********
	class Move final : public dae::GameObjectCommand
	{
	public:
		explicit Move(dae::GameObject* gameObject, const glm::vec2& direction, pacman::PlayerMovement* moveComp);
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
		explicit PressButton(dae::GameObject* gameObject);

		virtual void Execute() override;
	};

	// CHEAT COMMANDS
	//********
	class NextLevel final : public dae::Command
	{
	public:
		virtual void Execute() override;
	private:
		dae::EventQueue& m_eventQueue{ dae::EventQueue::GetInstance() };
	};

	// SOUND TOGGLE
	//********
	class ToggleSound final : public dae::Command
	{
	public:
		virtual void Execute() override;
	private:
		bool m_isOn{ true };
		SoundManager& m_soundManager{ SoundManager::GetInstance() };
	};
}
