#pragma once
#include "Component.h"
namespace dae
{
    class TextComponent;
}
namespace pacman
{
	class Font;

    class FPSComponent final : public dae::Component
    {
    public:
        explicit FPSComponent(dae::GameObject* owner);


        void Update(float elapsedSec) override;

    private:
        float m_FPS{ 0.0f };
        float m_cumulatedTime{ 0.0f };
        int m_frameCount{ 0 };
        dae::TextComponent* m_textComponent{};
    };
}
