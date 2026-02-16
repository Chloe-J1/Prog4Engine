#pragma once
#include <memory>
#include <string>
#include "Component.h"
namespace dae
{
	class Texture2D;
	class RenderComponent : public Component
	{
		std::shared_ptr<Texture2D> m_texture{};
	public:
		

		void SetTexture(const std::string& filename);
		virtual void Render() const override;
		virtual void FixedUpdate() override {};
		virtual void Update(float) override {};

		RenderComponent() = default;
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	};
	
}