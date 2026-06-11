#pragma once
// Base class for all components
namespace dae
{
	class GameObject;
	class CollisonManager;
	class Component
	{
	public:
		virtual void Start();
		virtual void Update(float elapsedSec);
		virtual void FixedUpdate();
		virtual void LateUpdate(float elapsedSec);
		virtual void Render() const;
		virtual void RenderUI();

		void SetHasStarted(bool hasStarted);
		bool GetHasStarted();
		bool GetIsAlive() const;
		void SetIsAlive(bool isAlive);
		GameObject* GetGameObject() const;
		bool GetIsEnabled() const;
		void SetIsEnabled(bool isEnabled);

		explicit Component(GameObject* owner);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
		virtual void OnCollision(GameObject*);
	private:

		GameObject* m_gameObject{};
		bool m_isAlive{ true };
		bool m_isEnabled{ true };
		bool m_hasStarted{ false };
	};
}