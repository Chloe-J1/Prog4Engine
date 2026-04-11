#pragma once
#include "Component.h"
#include <SDL3/SDL.h>
namespace dae
{
	class RenderComponent;
	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(GameObject* owner, int nrCols = 1, int nrRows = 1, float frameSec = 0, int row = 0);

		virtual void Update(float elapsedSec) override;

		float GetWidth() const;
		float GetHeight() const;
		void SetRow(int rowNr);
	private:
		int m_cols;
		int m_rows;
		int m_row;
		float m_frameSec;
		float m_width;
		float m_height;
		float m_textureWidth;
		float m_textureHeight;
		float m_accuSec;
		int m_actFrame;
		int m_nrFrames;

		SDL_FRect m_srcRect{};
		RenderComponent* m_renderComp;
	};
}
