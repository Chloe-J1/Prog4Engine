#pragma once
#include "Component.h"
#include <memory>
#include "ResourceManager.h"
#include "TextObject.h"
#include <SDL3/SDL_pixels.h> // used for color
#include <iostream>
namespace dae
{
	class Font;
	class TextObject;

    class FPSComponent final : public Component
    {
    public:
        FPSComponent()
        {
        }
        void Update(float elapsedSec) override
        {
            Component::Update(elapsedSec);

            //std::cout << elapsedSec << " " << m_cumulatedTime << "\n";
            m_cumulatedTime += elapsedSec;
            m_frameCount++;

            if (m_cumulatedTime >= 1.0f)
            {
                m_FPS = m_frameCount / m_cumulatedTime;
                std::string fpsText = "FPS: " + std::to_string((int)m_FPS);
                if (m_textObject)
                    m_textObject->SetText(fpsText);
                m_cumulatedTime -= 1.0f;
                m_frameCount = 0;
            }
        }

        
        void SetTextObject(TextObject* textObj) { m_textObject = textObj; }

    private:
        float m_FPS{ 0.0f };
        float m_cumulatedTime{ 0.0f };
        int m_frameCount{ 0 };
        std::shared_ptr<Font> m_font{};
        TextObject* m_textObject{nullptr};
        
    };
}
