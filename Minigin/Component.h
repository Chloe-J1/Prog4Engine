#pragma once
// Pure virtual base class for components
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update(float elapsedSec) = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

		bool GetIsAlive();
		void SetIsAlive(bool isAlive);

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