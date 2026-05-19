#include "FPSComponent.h"
#include <iostream>
#include "ResourceManager.h"
#include "TextComponent.h"

pacman::FPSComponent::FPSComponent(dae::GameObject* owner) :
    Component(owner)
{
    m_textComponent = GetGameObject()->GetComponent<dae::TextComponent>();
    if (m_textComponent == nullptr)
        std::cout << "TextComponent is nullptr\n";
}

void pacman::FPSComponent::Update(float elapsedSec)
{
    m_cumulatedTime += elapsedSec;
    m_frameCount++;

    if (m_cumulatedTime >= 1.0f)
    {
        m_FPS = m_frameCount / m_cumulatedTime;
        std::string fpsText = "FPS: " + std::to_string((int)m_FPS);
        if (m_textComponent)
            m_textComponent->SetText(fpsText);
        m_cumulatedTime = 0.0f;
        m_frameCount = 0;
    }
}
