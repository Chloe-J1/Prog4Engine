#include "GameObject.h"
#include "Component.h"
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
		for (int index{0}; index < m_components.size(); index++)
		{
			if (not m_components[index]->dae::Component::GetIsAlive())
			{
				m_components.erase(m_components.begin() + index);
			}
			else
			{
				m_components[index]->LateUpdate(elapsedSec);
			}
		}

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
		component->m_gameObject = this;
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


template<typename T>
void dae::GameObject::RemoveComponent(const T* component)
{
	if (m_isAlive)
	{
		for (auto& comp : m_components) {
			if (comp == component) // Mss components een naam geven en op basis daarvan removen?
			{
				Component* removeComp = dynamic_cast<T&>(*comp);
				removeComp->SetIsAlive(false);
				return;
			}
		}
	}

}


