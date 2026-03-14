#pragma once
#include <glm/glm.hpp>
namespace dae
{
	enum class TriggerEvent
	{
		PressedThisFrame,
		ReleasedThisFrame,
		Hold
	};
	class GameObject;
	class MoveComponent;
	// BASE COMMAND
	//********
	class Command
	{
	public:
		Command(TriggerEvent eventType);
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute(float elapsedSec) = 0;
		TriggerEvent GetEventType();

	private:
		TriggerEvent m_eventType;
	};
	// GAME OBJ COMMAND
	//********
	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(TriggerEvent eventType, GameObject* gameObject):
			Command(eventType)
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

	// MOVE
	//********
	class Move final : public GameObjectCommand
	{
	public:
		Move(TriggerEvent eventType, GameObject* gameObject, const glm::vec2& direction) :
			GameObjectCommand(eventType, gameObject),
			m_direction{direction}
		{}

		virtual void Execute(float elapsedSec) override;
		
	private:
		glm::vec2 m_direction;
	};
}
