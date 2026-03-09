#pragma once
#include "GameObject.h"
#include "MoveComponent.h"
namespace dae
{
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


	class Jump final : public GameObjectCommand
	{
	public:
		Jump(GameObject* gameObject) : GameObjectCommand(gameObject) {}

		void Execute() override
		{
			MoveComponent* move = GetGameObject()->GetComponent<MoveComponent>();
			if (move)
				move->Jump();
		}
	};
}
