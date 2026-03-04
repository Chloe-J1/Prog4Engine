#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include <SDL3/SDL.h>
#include <string>
namespace dae
{
	class Texture2D;
	class RenderComponent : public Component
	{
	public:

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		virtual void Render() const override;
		virtual void Update(float elapsedSec) override;

		RenderComponent(GameObject* owner, const std::string& filepath, int nrCols = 1, int nrRows = 1, float frameSec = 0, int row = 0);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_texture{};
		int m_Cols;
		int m_Rows;
		int m_Row;
		float m_Width;
		float m_Height;
		float m_FrameSec;
		float m_AccuSec;
		int   m_ActFrame;
		int m_NrFrames;
		SDL_FRect m_srcRect;
		SDL_FRect m_dstRect;
	};
	
}