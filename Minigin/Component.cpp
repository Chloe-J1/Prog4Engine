#include "Component.h"
#include "Component.h"
#include "Component.h"
#include "Component.h"


void dae::Component::Start()
{
}

void dae::Component::Update(float)
{
}

void dae::Component::FixedUpdate()
{
}

void dae::Component::LateUpdate(float)
{
}

void dae::Component::Render() const
{
}

void dae::Component::RenderUI()
{
}

void dae::Component::SetHasStarted(bool hasStarted)
{
	m_hasStarted = hasStarted;
}

bool dae::Component::GetHasStarted()
{
	return m_hasStarted;
}

bool dae::Component::GetIsAlive() const
{
	return m_isAlive;
}

void dae::Component::SetIsAlive(bool isAlive)
{
	m_isAlive = isAlive;
}

dae::GameObject* dae::Component::GetGameObject() const
{
	return m_gameObject;
}

bool dae::Component::GetIsEnabled() const
{
	return m_isEnabled;
}

void dae::Component::SetIsEnabled(bool isEnabled)
{
	m_isEnabled = isEnabled;
}

dae::Component::Component(GameObject* owner):
	m_gameObject{owner}
{
}
