#include "GameObject.h"
#include "Component.h"
#include <algorithm>
#include <iostream>

dae::GameObject::~GameObject()
{
	for (const auto& comp : m_components)
	{
		delete comp;
	}
}

void dae::GameObject::Update(float elapsedSec)
{
	if (m_isAlive)
	{

		for (const auto& comp : m_components)
		{
			comp->Update(elapsedSec);
		}
	}

	
}

void dae::GameObject::FixedUpdate()
{
	if (m_isAlive)
	{
		for (const auto& comp : m_components)
		{
			comp->FixedUpdate();
		}
	}
}

void dae::GameObject::LateUpdate(float elapsedSec)
{
	if (m_isAlive)
	{
		for (const auto& comp : m_components)
		{
			comp->LateUpdate(elapsedSec);
		}
	}
}

void dae::GameObject::Cleanup()
{
	if (m_isAlive)
	{
		auto lastAlive = std::partition(m_components.begin(), m_components.end(), [](Component* comp) { return comp->GetIsAlive(); });

		m_components.erase(lastAlive, m_components.end());
	}
}

void dae::GameObject::Render() const
{
	if (m_isAlive)
	{
		for (const auto& comp : m_components)
		{
			comp->Render();
		}
	}
	
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_transform;
}

void dae::GameObject::AddComponent(Component* component)
{
	if (m_isAlive)
	{
		m_components.emplace_back(component);

	}
}

void dae::GameObject::SetIsAlive(bool isAlive)
{
	m_isAlive = isAlive;
}

bool dae::GameObject::GetIsAlive()
{
	return m_isAlive;
}




