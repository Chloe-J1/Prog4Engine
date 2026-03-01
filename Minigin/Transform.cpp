#include "Transform.h"
#include "GameObject.h"


dae::Transform::Transform(GameObject* parent):
	m_gameObject{parent}
{
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_isPositionDirty)
		UpdateWorldPosition();
	return m_worldPosition;
}

void dae::Transform::SetLocalPosition(const glm::vec3& newPos)
{
	m_localPosition = newPos;
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

bool dae::Transform::GetPositionDirty() const
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


