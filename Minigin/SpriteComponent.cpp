#include "SpriteComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"

dae::SpriteComponent::SpriteComponent(GameObject* owner, int nrCols, int nrRows, float frameSec, int row):
	Component(owner),
	m_cols{ nrCols },
	m_rows{ nrRows },
	m_row{ row },
	m_frameSec{ frameSec },
	m_accuSec{ 0 },
	m_actFrame{ 0 },
	m_nrFrames{ nrCols }
{
	m_renderComp = GetGameObject()->GetComponent<RenderComponent>();
	m_textureWidth = m_renderComp->GetWidth();
	m_textureHeight = m_renderComp->GetHeight();
	m_width = m_renderComp->GetWidth() / nrCols;
	m_height = m_renderComp->GetHeight() / m_rows;
	m_renderComp->SetDstSize(m_width, m_height);
}

void dae::SpriteComponent::Update(float elapsedSec)
{
	// Calculate frame
	m_accuSec += elapsedSec;
	if (m_accuSec > m_frameSec)
	{
		++m_actFrame;
		if (m_actFrame >= m_nrFrames)
		{
			m_actFrame = 0;
		}
		m_accuSec -= m_frameSec;
	}
	if (m_actFrame >= m_nrFrames)
	{
		m_actFrame = 0;
	}

	// Update srcRect
	m_srcRect.w = m_width;
	m_srcRect.h = m_height;
	m_srcRect.x = m_actFrame % m_cols * m_width;
	m_srcRect.y = m_actFrame / m_cols * m_height + m_height * m_row;
	m_renderComp->SetSrcRect(m_srcRect);
	
}

float dae::SpriteComponent::GetWidth() const
{
	return m_width;
}

float dae::SpriteComponent::GetHeight() const
{
	return m_height;
}

void dae::SpriteComponent::SetRow(int rowNr)
{
	m_row = rowNr;
}
