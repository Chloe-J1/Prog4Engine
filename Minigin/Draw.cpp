#include "Draw.h"
#include <glm/glm.hpp>

void dae::Draw::FillRect([[maybe_unused]] const glm::vec2& pos, [[maybe_unused]] float width, [[maybe_unused]] float height)
{
	SDL_FRect rect{ pos.x, pos.y, width, height };
	SDL_RenderFillRect(m_renderer, &rect);
}

void dae::Draw::FillRect([[maybe_unused]] float x, [[maybe_unused]] float y, [[maybe_unused]] float width, [[maybe_unused]] float height)
{
	FillRect(glm::vec2{ x,y }, width, height);
}

void dae::Draw::DrawRect([[maybe_unused]] const glm::vec2& pos, [[maybe_unused]] float width, [[maybe_unused]] float height)
{
	SDL_FRect rect{ pos.x, pos.y, width, height };
	SDL_RenderRect(m_renderer, &rect);
}

void dae::Draw::DrawRect([[maybe_unused]] float x, [[maybe_unused]] float y, [[maybe_unused]] float width, [[maybe_unused]] float height)
{
	DrawRect(glm::vec2{ x,y }, width, height);
}

void dae::Draw::SetColor([[maybe_unused]] Uint8 r, [[maybe_unused]] Uint8 g, [[maybe_unused]] Uint8 b, [[maybe_unused]] Uint8 a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}
