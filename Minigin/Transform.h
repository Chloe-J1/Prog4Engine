#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;
	class Transform final
	{
	public:
		Transform(GameObject* gameObject);
		~Transform() = default;
		Transform(const Transform& other) = default;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::vec3& GetWorldPosition();
		void SetLocalPosition(const glm::vec3& newPos);
		void SetLocalPosition(const glm::vec2& newPos);
		void AddLocalPosition(const glm::vec2& deltaMovement);
		void SetPositionDirty();
		bool GetIsPositionDirty() const;
		

		
	private:
		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};
		bool m_isPositionDirty{ false };
		GameObject* m_gameObject;

		void UpdateWorldPosition();
	};
}
