#pragma once
#include "Component.h"
#include <memory>
#include "ResourceManager.h"
#include "TextComponent.h"
#include <SDL3/SDL_pixels.h> // used for color
#include <iostream>
namespace dae
{
	class Font;
	class TextObject;

    class FPSComponent final : public Component
    {
    public:
        FPSComponent(dae::GameObject* owner):
            Component(owner)
        {
        }
        virtual ~FPSComponent() = default;
        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        Component& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;

        void Update(float elapsedSec) override
        {
            Component::Update(elapsedSec);

            // TODO: make a Start() function where i can initialize these members
            m_textComponent = GetGameObject()->GetComponent<TextComponent>();
            if (m_textComponent == nullptr)
                std::cout << "TextComponent is nullptr\n";

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

    private:
        float m_FPS{ 0.0f };
        float m_cumulatedTime{ 0.0f };
        int m_frameCount{ 0 };
        std::shared_ptr<Font> m_font{};
        TextComponent* m_textComponent{};
    };
}
