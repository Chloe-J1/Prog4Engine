#include "GameObject.h"
#include "Component.h"
#include <algorithm>
#include <iostream>

dae::GameObject::GameObject():
	m_transform{Transform(this)}
{
}

dae::GameObject::~GameObject()
{
	for (const auto& comp : m_components)
	{
		delete comp;
	}
	for (const auto& child : m_childObjects)
	{
		child->SetIsAlive(false);
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

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_transform.SetLocalPosition(glm::vec3(x, y, 0.0f));
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_transform;
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	return m_transform.GetWorldPosition();
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
		m_transform.SetLocalPosition(m_transform.GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			m_transform.SetLocalPosition(m_transform.GetWorldPosition() - parent->m_transform.GetWorldPosition());
		m_transform.SetPositionDirty();
	}
	if (m_parent) m_parent->RemoveChild(this);
	m_parent = parent;
	if (m_parent) m_parent->AddChild(this);
}

bool dae::GameObject::IsChild(GameObject* parent) // fout
{
	if(parent == m_parent)
		return true;
	return false;
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	if (child == nullptr) return;

	auto itr = std::find(m_childObjects.begin(), m_childObjects.end(), child);

	
	if (itr == m_childObjects.end()) return; // child not in container


	// no longer child object of this parent
	m_childObjects.erase(itr);
	child->SetParent(nullptr, false);

}

void dae::GameObject::AddChild(GameObject* child)
{
	if (child != nullptr && child != this)
	{
		m_childObjects.emplace_back(child);

		child->GetTransform().SetPositionDirty();
	}
}

dae::GameObject* dae::GameObject::GetParent()
{
	return m_parent;
}

void dae::GameObject::SetPositionDirty()
{
	m_transform.SetPositionDirty(); // check if ok 
}

std::vector<dae::GameObject*> dae::GameObject::GetChildren()
{
	return m_childObjects;
}

void dae::GameObject::SetIsAlive(bool isAlive)
{
	m_isAlive = isAlive;
}

bool dae::GameObject::GetIsAlive()
{
	return m_isAlive;
}




