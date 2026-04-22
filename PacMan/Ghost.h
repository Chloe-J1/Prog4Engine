#pragma once
#include "../Minigin/Component.h"
#include "GameObject.h"
#include <vector>
#include <iostream>
namespace pacman
{
	class GhostComponent final : public dae::Component
	{
	public:
		GhostComponent(dae::GameObject* owner) :
			Component(owner),
			m_damage{1}
		{
			m_transform = &GetGameObject()->GetTransform();

			// Hard coded path -> remove this
			m_path.push_back(glm::vec2{ 28,26 });
			m_path.push_back(glm::vec2{ 100,26 });
			m_path.push_back(glm::vec2{ 28,26 });
			m_path.push_back(glm::vec2{ 28,256 });
		}

		int GetDamage() const
		{
			return m_damage;
		}

		virtual void Update(float elapsedSec) override
		{
			FollowPath(elapsedSec);
		}

	private:
		int m_damage;
		std::vector<glm::vec2> m_path;
		dae::Transform* m_transform;
		int m_pathIdx{ 0 };
		float m_moveSpeed{ 50.f };

		void FollowPath(float elapsedSec)
		{
			if (m_path.empty()) return; // No path so early exit

			glm::vec2 direction = m_path[m_pathIdx] - glm::vec2{ m_transform->GetWorldPosition() };
			float distance = glm::length(direction);
			const float threshold{ 1.f };
			if (distance < threshold)
			{
				// Go to next point
				++m_pathIdx;
				if (m_pathIdx >= m_path.size())
				{
					m_pathIdx = 0;
				}
			}
			else
			{
				// Move towards point
				glm::vec2 deltaMovement = glm::normalize(direction) * m_moveSpeed * elapsedSec;
				m_transform->AddLocalPosition(deltaMovement);
			}
		}
	};
}