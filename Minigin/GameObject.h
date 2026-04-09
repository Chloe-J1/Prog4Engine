#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include <glm/glm.hpp>
#include "Transform.h"
#include <string>

namespace dae
{
	class Texture2D;
	
	class GameObject final
	{

	public:
		void Update(float elapsedSec);
		void FixedUpdate();
		void LateUpdate(float elapsedSec);
		void Cleanup();
		void Render() const;
		void RenderUI();

		// Transform
		void SetLocalPosition(float x, float y);
		void AddLocalPosition(const glm::vec2& deltaMovement);
		Transform GetTransform() const;
		const glm::vec3& GetWorldPosition();

		// Components
		template<typename T, typename... Args>
		// Variadic template so that the user is forced to instantiate the component on the right owner
		void AddComponent(Args&&... args)
		{
			auto newComp = std::make_unique<T>(this, std::forward<Args>(args)...);
			m_components.emplace_back(std::move(newComp));
		}
		template<typename T>
		void RemoveComponent()
		{
			for (const auto& comp : m_components)
			{
				if (dynamic_cast<T*>(comp.get()))
				{
					comp->SetIsAlive(false);
				}
			}
		}
		template<typename T>
		T* GetComponent() const
		{
			for (const auto& comp : m_components)
			{
				if (T* castedComp = dynamic_cast<T*>(comp.get()))
				{
					return castedComp;
				}
			}
			return nullptr;
		}
		template<typename T>
		bool HasComponent() const
		{
			for (const auto& comp : m_components)
			{
				if (T* castedComp = dynamic_cast<T*>(comp.get()))
				{
					return true;
				}
			}
			return false;
		}

		// Parenting
		void SetParent(GameObject* parent, bool keepWorldPosition);
		bool IsChild(GameObject* parent);
		GameObject* GetParent();
		void SetPositionDirty();
		std::vector<GameObject*> GetChildren();

		// Destroy
		void SetIsAlive(bool isAlive);
		bool GetIsAlive();
		
		// Collision
		void OnCollision(GameObject* other);
		void SetLayer(const std::string& layer);
		const std::string& GetLayer() const;

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		Transform m_transform;
		std::vector<std::unique_ptr<Component>> m_components;
		bool m_isAlive{ true };

		GameObject* m_parent{}; // not owner
		std::vector<GameObject*> m_childObjects;
		
		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);

		std::string m_layer{"default"};
	};
	
}
