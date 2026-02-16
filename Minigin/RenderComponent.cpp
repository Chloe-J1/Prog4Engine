#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::Render() const
{
	Component::Render();
	Transform transform = m_gameObject->GetTransform();
	glm::vec3 pos = transform.GetPosition();

	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}