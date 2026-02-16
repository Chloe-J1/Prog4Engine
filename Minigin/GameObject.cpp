#include "GameObject.h"
#include "Component.h"


dae::GameObject::~GameObject()
{
	for (const auto& comp : m_components)
	{
		delete comp;
	}
}

void dae::GameObject::Update(float elapsedSec)
{
	for (const auto& comp : m_components)
	{
		comp->Update(elapsedSec);
	}
}

void dae::GameObject::FixedUpdate()
{
	for (const auto& comp : m_components)
	{
		comp->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& comp : m_components)
	{
		comp->Render();
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
	component->m_gameObject = this;
	m_components.emplace_back(component);
}

template<typename T>
void dae::GameObject::RemoveComponent(const T* component)
{
	for (auto& comp : m_components) {
		if (comp == component) 
		{
			Component* removeComp = dynamic_cast<T&>(*comp);
			removeComp->SetIsAlive(false);
			return;
		}
	}

}


