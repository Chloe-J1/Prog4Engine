#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"
#include <iostream>


dae::RenderComponent::RenderComponent(GameObject* owner, const std::string& filepath):
	Component(owner)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filepath);
	if (m_texture == nullptr)
		std::cout << "Couldn't load " << filepath << "\n";

	m_dstRect.x = m_dstRect.y = m_srcRect.x = m_srcRect.y = 0;
	m_dstRect.w = m_srcRect.w = m_texture->GetWidth();
	m_dstRect.h = m_srcRect.h = m_texture->GetHeight();

	m_owner = owner;
}

dae::RenderComponent::RenderComponent(GameObject* owner):
	Component(owner)
{
	m_useSrcRect = false;
	m_owner = owner;
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

	if (m_useSrcRect)
		Renderer::GetInstance().RenderTexture(*m_texture, m_srcRect, m_dstRect);
	else
		Renderer::GetInstance().RenderTexture(*m_texture, m_owner->GetWorldPosition().x, m_owner->GetWorldPosition().y);
}

void dae::RenderComponent::Update(float)
{
	// Update dstRect position to the position of the Go
	glm::vec3 pos{ m_owner->GetWorldPosition()};

	m_dstRect.x = pos.x;
	m_dstRect.y = pos.y;
}

float dae::RenderComponent::GetWidth() const
{
	return m_texture->GetWidth();
}

float dae::RenderComponent::GetHeight() const
{
	return m_texture->GetHeight();
}

void dae::RenderComponent::SetSrcRect(const SDL_FRect& srcRect)
{
	m_srcRect = srcRect;
}

void dae::RenderComponent::SetDstSize(float width, float height)
{
	m_dstRect.w = width;
	m_dstRect.h = height;
}

