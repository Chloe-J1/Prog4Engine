#include "RotationComponent.h"
#include "Transform.h"
#include "GameObject.h"

void dae::RotationComponent::Update(float elapsedSec)
{
    float offsetX{};
    float offsetY{};

    if (m_isClockwise)
    {
        m_currAngle += m_stepAngle * elapsedSec;
    }
    else
    {
        m_currAngle -= m_stepAngle * elapsedSec;
    }
    
    if (m_currAngle >= 360.f)
        m_currAngle = 0.f;

    
    glm::vec3 center{ GetGameObject()->GetWorldPosition() };
    if (GameObject* parent = GetGameObject()->GetParent())
    {
        // Child object pos is already relative to parent
        offsetX = cos(m_currAngle) * m_radius;
        offsetY = sin(m_currAngle) * m_radius;
    }
    else
    {
        offsetX = center.x + cos(m_currAngle) * m_radius;
        offsetY = center.y + sin(m_currAngle) * m_radius;
    }

    

    GetGameObject()->SetLocalPosition({ offsetX, offsetY, 0.f });
    
}
