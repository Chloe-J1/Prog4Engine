#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"



namespace dae
{
	class Font;
	class Texture2D;
	class RenderComponent;
	class TextComponent final : public Component
	{
	public:
		void Update(float elapsedSec) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

		TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255, 255 });
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		std::shared_ptr<Font> m_font{};
		std::shared_ptr<Texture2D> m_textTexture{};
		RenderComponent* m_renderComp;
	};
}
