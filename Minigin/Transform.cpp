#include "Transform.h"
#include "Transform.h"
#include "GameObject.h"

#include <iostream>


dae::Transform::Transform(GameObject* parent):
	m_gameObject{parent}
{
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_isPositionDirty)
	{
		UpdateWorldPosition();
	}
	return m_worldPosition;
}

void dae::Transform::SetLocalPosition(const glm::vec3& newPos)
{
	m_localPosition = newPos;
	SetPositionDirty();
}

void dae::Transform::SetLocalPosition(const glm::vec2& newPos)
{
	SetLocalPosition(glm::vec3{ newPos, 0 });
}

void dae::Transform::AddLocalPosition(const glm::vec2& deltaMovement)
{
	m_localPosition.x += deltaMovement.x;
	m_localPosition.y += deltaMovement.y;
	SetPositionDirty();
}

void dae::Transform::SetPositionDirty()
{
	m_isPositionDirty = true;
	for (const auto& child : m_gameObject->GetChildren())
	{
		child->SetPositionDirty();
	}
}

bool dae::Transform::GetIsPositionDirty() const
{
	return m_isPositionDirty;
}

void dae::Transform::UpdateWorldPosition()
{
	if (m_isPositionDirty)
	{
		if (m_gameObject->GetParent() == nullptr)
			m_worldPosition = m_localPosition;
		else
		{
			m_worldPosition = m_gameObject->GetParent()->GetWorldPosition() + m_localPosition;
		}
	}
	m_isPositionDirty = false;
}


