#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include <SDL3/SDL.h>
#include <glm/fwd.hpp>
#include "Renderer.h"
#include "ResourceManager.h"
namespace dae
{
	class Texture2D;
	class GameObject;
	class RenderComponent final : public Component
	{
	public:

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);

		float GetWidth() const;
		float GetHeight() const;

		void SetSrcRect(const SDL_FRect& srcRect);
		void SetDstSize(float width, float height);

		explicit RenderComponent(GameObject* owner, const std::string& filepath);
		explicit RenderComponent(GameObject* owner);
	private:
		void Render() const;
		void Update(float elapsedSec);
		std::shared_ptr<Texture2D> m_texture{};

		SDL_FRect m_srcRect{};
		SDL_FRect m_dstRect{};

		GameObject* m_owner;
		bool m_useSrcRect{ true };

		Renderer& m_renderer{ Renderer::GetInstance() };
		ResourceManager& m_resourceManager{ ResourceManager::GetInstance() };
	};
	
}