#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
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

	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

dae::RenderComponent::RenderComponent(GameObject* owner):
	Component(owner)
{
}
