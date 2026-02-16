#pragma once
// Base class for all components
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update(float) { if (not m_isAlive) return; };
		virtual void FixedUpdate() { if (not m_isAlive) return; };
		virtual void LateUpdate(float) { if (not m_isAlive) return; };
		virtual void Render() const { if (not m_isAlive) return; };

		bool GetIsAlive() { return m_isAlive; };
		void SetIsAlive(bool isAlive) { m_isAlive = isAlive; };
		GameObject* GetGameObject() { return m_gameObject; };

		Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		GameObject* m_gameObject{};

	private:
		bool m_isAlive{ true };
	};
}