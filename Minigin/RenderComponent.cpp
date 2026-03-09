#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"
#include <iostream>

dae::RenderComponent::RenderComponent(GameObject* owner, const std::string& filepath, int nrCols, int nrRows, float frameSec, int row):
	Component(owner),
	m_Cols{nrCols},
	m_Rows{nrRows},
	m_FrameSec{frameSec},
	m_Row{row},
	m_AccuSec{0},
	m_ActFrame{0},
	m_NrFrames{nrCols}
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filepath);
	if (m_texture == nullptr)
		std::cout << "Couldn't load " << filepath << "\n";


	m_Width = m_texture->GetWidth() / m_Cols;
	m_Height = m_texture->GetHeight() / m_Rows;
	m_dstRect.x = m_dstRect.y = 0;
	m_dstRect.w = m_Width;
	m_dstRect.h = m_Height;
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	if (m_texture == nullptr)
		std::cout << "Couldn't load " << filename << "\n";
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_texture = texture;
}

void dae::RenderComponent::Render() const
{
	if (m_texture == nullptr) return;
	Component::Render();
	Transform transform = GetGameObject()->GetTransform();
	glm::vec3 pos = transform.GetWorldPosition();

	Renderer::GetInstance().RenderTexture(*m_texture, m_srcRect, m_dstRect);
}

void dae::RenderComponent::Update(float elapsedSec)
{
	if (m_texture == nullptr) return;
	// Calculate frame
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameSec)
	{
		if (m_ActFrame >= m_NrFrames)
		{
			m_ActFrame = 0;
		}
		++m_ActFrame;
		m_AccuSec -= m_FrameSec;
	}
	if (m_ActFrame >= m_NrFrames)
	{
		m_ActFrame = 0;
	}

	// Update srcRect
	m_srcRect.w = m_texture->GetWidth() / m_Cols;
	m_srcRect.h = m_texture->GetHeight() / m_Rows;
	m_srcRect.x = m_ActFrame % m_Cols * m_Width;
	m_srcRect.y = m_ActFrame / m_Cols * m_Height + m_Height * m_Row;

	// Update dstRect position to the position of the player
	glm::vec3 pos{ GetGameObject()->GetWorldPosition() };
	m_dstRect.x = pos.x;
	m_dstRect.y = pos.y;
}

