#pragma once
#include <glm/glm.hpp>
namespace dae
{
	enum TriggerEvent
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
		virtual ~Command() = default; // rule of 5

		virtual void Execute() = 0;
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

		virtual void Execute() override;
		
	private:
		glm::vec2 m_direction;
	};
}
