#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include <glm/glm.hpp>
#include "Transform.h"

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

		// Transform
		void SetLocalPosition(float x, float y);
		Transform GetTransform() const;
		const glm::vec3& GetWorldPosition();

		// Components
		void AddComponent(Component* component);
		template<typename T>
		void RemoveComponent()
		{
			for (int index{0}; index < (int)m_components.size(); ++index)
			{
				if (T* removeComp = dynamic_cast<T*>(m_components[index]))
				{
					m_components[index]->SetIsAlive(false);
				}
			}
		}
		template<typename T>
		T* GetComponent() const
		{
			for (const auto& comp : m_components)
			{
				if (T* castedComp = dynamic_cast<T*>(comp))
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
				if (T* castedComp = dynamic_cast<T*>(comp))
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
		

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		Transform m_transform;
		std::vector<Component*> m_components; // Make this unique ptr
		std::vector<Component*> m_aliveComponents;
		bool m_isAlive{ true };

		GameObject* m_parent{}; // not owner
		
		bool m_isPositionDirty{ false };
		std::vector<GameObject*> m_childObjects;

		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);
	};
	
}
