#include "DebugDraw.h"

void dae::DebugDraw::FillRect([[maybe_unused]] const glm::vec2& pos, [[maybe_unused]] float width, [[maybe_unused]] float height)
{
#ifdef _DEBUG
	SDL_FRect rect{ pos.x, pos.y, width, height };
	SDL_RenderFillRect(m_renderer, &rect);
#endif // DEBUG
}

void dae::DebugDraw::DrawRect([[maybe_unused]] const glm::vec2& pos, [[maybe_unused]] float width, [[maybe_unused]] float height)
{
#ifdef _DEBUG
	SDL_FRect rect{ pos.x, pos.y, width, height };
	SDL_RenderRect(m_renderer, &rect);
#endif // _DEBUG
}

void dae::DebugDraw::SetColor([[maybe_unused]] Uint8 r, [[maybe_unused]] Uint8 g, [[maybe_unused]] Uint8 b, [[maybe_unused]] Uint8 a)
{
#ifdef _DEBUG
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
#endif // _DEBUG
}
