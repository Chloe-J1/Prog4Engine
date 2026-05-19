#include "Command.h"

dae::GameObjectCommand::GameObjectCommand(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

dae::GameObject* dae::GameObjectCommand::GetGameObject() const
{
	return m_gameObject;
}
