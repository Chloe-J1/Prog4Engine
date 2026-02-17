#pragma once
#include "Transform.h"
#include <vector>
#include <memory>

namespace dae
{
	class Texture2D;
	class Component;
	
	class GameObject final
	{

	public:
		virtual void Update(float elapsedSec);
		virtual void FixedUpdate();
		virtual void LateUpdate(float elapsedSec);
		virtual void Render() const;

		// Transform
		void SetPosition(float x, float y);
		Transform GetTransform() const;

		// Components
		void AddComponent(Component* component);
		template<typename T>
		void RemoveComponent(const T* component);
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

		void SetIsAlive(bool isAlive);
		bool GetIsAlive();
		

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		Transform m_transform{};
		std::vector<Component*> m_components;
		bool m_isAlive{ true };
	};
	
}
