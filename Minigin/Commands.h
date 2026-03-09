#pragma once
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


	class Jump final : public GameObjectCommand
	{
	public:
		Jump(GameObject* gameObject) : GameObjectCommand(gameObject) {}

		virtual void Execute() override;
	};
}
