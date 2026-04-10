#pragma once
#include "GameObject.h"
namespace dae
{
	// BASE COMMAND
	//********
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute() = 0;
	};
	// GAME OBJ COMMAND
	//********
	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject* gameObject)
		{
			m_gameObject = gameObject;
		}

		virtual ~GameObjectCommand() = default;
		GameObjectCommand(const GameObjectCommand& other) = delete;
		GameObjectCommand(GameObjectCommand&& other) = delete;
		GameObjectCommand& operator=(const GameObjectCommand& other) = delete;
		GameObjectCommand& operator=(GameObjectCommand&& other) = delete;
	protected:
		GameObject* GetGameObject() const { return m_gameObject; }
	private:
		GameObject* m_gameObject;
	};
}