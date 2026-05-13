#pragma once
#include "../Minigin/Singleton.h"
#include "../Minigin/Renderer.h"
#include <glm/glm.hpp>

namespace dae
{
	class DebugDraw final : public Singleton<DebugDraw>
	{
	public:
		void FillRect(const glm::vec2& pos, float width, float height);
		void DrawRect(const glm::vec2& pos, float width, float height);
		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	private:
		SDL_Renderer* m_renderer{ Renderer::GetInstance().GetSDLRenderer() };
	};
}