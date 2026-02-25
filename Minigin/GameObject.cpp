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
		UpdateWorldPosition(); //
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
	SetPositionDirty();
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

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_parent == parent)
		return;
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		SetPositionDirty();
	}
	if (m_parent) m_parent->RemoveChild(this);
	m_parent = parent;
	if (m_parent) m_parent->AddChild(this);
}

bool dae::GameObject::IsChild(GameObject* parent)
{
	if(parent == m_parent)
		return true;
	return false;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& newPos)
{
	m_localPosition = newPos;
	SetPositionDirty();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_isPositionDirty)
		UpdateWorldPosition();
	return m_worldPosition;
}

void dae::GameObject::SetPositionDirty()
{
	m_isPositionDirty = true;
	for (auto& child : m_childObjects)
	{
		child->SetPositionDirty();
	}
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	if (child == this || child == nullptr) return;
	for (auto& c : m_childObjects)
	{
		if (c == child)
			c->SetIsAlive(false);
	}
}

void dae::GameObject::AddChild(GameObject* child)
{
	if (child != nullptr && child != this)
	{
		m_childObjects.emplace_back(child);

		child->SetPositionDirty();
	}
}

void dae::GameObject::UpdateWorldPosition()
{

	if (m_isPositionDirty)
	{
		if (m_parent == nullptr)
			m_worldPosition = m_localPosition;
		else
		{
			m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;
		}
	}
	m_transform.SetPosition(m_worldPosition.x, m_worldPosition.y, m_worldPosition.z); // draw on correct pos
	m_isPositionDirty = false;
}

dae::GameObject* dae::GameObject::GetParent()
{
	return m_parent;
}

void dae::GameObject::SetIsAlive(bool isAlive)
{
	m_isAlive = isAlive;
}

bool dae::GameObject::GetIsAlive()
{
	return m_isAlive;
}




