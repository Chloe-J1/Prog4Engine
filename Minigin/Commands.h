#pragma once
#include <glm/glm.hpp>
namespace dae
{
	class GameObject;
	class MoveComponent;
	class Command
	{
	public:
		virtual ~Command() = default; // rule of 5
		virtual void Execute() = 0;
	};

	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject* gameObject) { m_gameObject = gameObject; }
		virtual ~GameObjectCommand() = default;
	protected:
		GameObject* GetGameObject() const { return m_gameObject; }
	private:
		GameObject* m_gameObject;
	};


	class Move final : public GameObjectCommand
	{
	public:
		Move(GameObject* gameObject, const glm::vec2& direction) :
			GameObjectCommand(gameObject),
			m_direction{direction}
		{}

		virtual void Execute() override;

	private:
		glm::vec2 m_direction;
	};
}
