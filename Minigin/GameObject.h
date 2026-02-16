#pragma once
#include "Transform.h"
#include <vector>
#include <memory>

namespace dae
{
	class Texture2D;
	class Component;
	
	class GameObject 
	{

	public:
		virtual void Update(float elapsedSec);
		virtual void FixedUpdate();
		virtual void Render() const;

		void SetPosition(float x, float y);
		Transform GetTransform() const;

		void AddComponent(Component* component);
		template<typename T>
		void RemoveComponent(const T* component);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		Transform m_transform{};
		std::vector<Component*> m_components;
	};
	
}
