#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include <SDL3/SDL.h>
#include <glm/fwd.hpp>
namespace dae
{
	class Texture2D;
	class GameObject;
	class RenderComponent : public Component
	{
	public:

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		virtual void Render() const override;
		virtual void Update(float elapsedSec) override;

		float GetWidth() const;
		float GetHeight() const;
		
		void SetSrcRect(const SDL_FRect& srcRect);
		void SetDstSize(float width, float height);

		RenderComponent(GameObject* owner, const std::string& filepath);
		RenderComponent(GameObject* owner);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_texture{};
		
		SDL_FRect m_srcRect;
		SDL_FRect m_dstRect;

		GameObject* m_owner;
		bool m_useSrcRect{ true };
	};
	
}