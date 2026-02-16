#include "Component.h"

bool dae::Component::GetIsAlive()
{
    return m_isAlive;
}

void dae::Component::SetIsAlive(bool isAlive)
{
    m_isAlive = isAlive;
}
