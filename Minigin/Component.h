#pragma once
// Base class for all components
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update(float) { };
		virtual void FixedUpdate() { };
		virtual void LateUpdate(float) {  };
		virtual void Render() const { };

		bool GetIsAlive() { return m_isAlive; };
		void SetIsAlive(bool isAlive) { m_isAlive = isAlive; };
		GameObject* GetGameObject() const { return m_gameObject; };

		Component(GameObject* owner) { m_gameObject = owner; };
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;


	protected:
		GameObject* m_gameObject{};
		bool m_isAlive{ true };
	};
}