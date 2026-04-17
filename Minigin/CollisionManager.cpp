#include "CollisionManager.h"
#include "Hitbox.h"
#include <iostream>
#include "GameObject.h"

void dae::CollisionManager::AddHitbox(Hitbox* hitbox)
{
	m_hitboxes.emplace_back(hitbox);
}

void dae::CollisionManager::RemoveHitbox(Hitbox* hitbox)
{
	auto itr = std::find(m_hitboxes.begin(), m_hitboxes.end(), hitbox);
	if (itr == m_hitboxes.end()) return; // no such hitbox found
	m_hitboxes.erase(itr);
}

void dae::CollisionManager::CheckOverlapping()
{
	for (int index = 0; index < (int)m_hitboxes.size(); index++)
	{
		Hitbox* hitbox = m_hitboxes[index];

		for (int indexOther = index; indexOther < (int)m_hitboxes.size(); indexOther++)
		{
			Hitbox* hitboxOther = m_hitboxes[indexOther];
			if (hitboxOther == hitbox) continue; // Don't calculate IsHit with itself

			if (hitbox->IsHit(*hitboxOther))
			{
				// Call collision on all components
				GameObject* thisObj = hitbox->GetGameObject();
				GameObject* otherObj = hitboxOther->GetGameObject();

				for (const auto& comp : thisObj->GetAllComponents())
				{
					comp->OnCollision(otherObj); 
				}
				for (const auto& comp : otherObj->GetAllComponents())
				{
					comp->OnCollision(thisObj);
				}
			}
		}
	}
}
