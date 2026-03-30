#include "CollisionManager.h"
#include "Hitbox.h"
#include <iostream>
#include "GameObject.h"

void dae::CollisionManager::AddHitbox(Hitbox* hitbox)
{
	m_hitboxes.emplace_back(hitbox);
	std::cout << "hitbox added\n";
}

void dae::CollisionManager::RemoveHitbox(Hitbox* hitbox)
{
	auto itr = std::find(m_hitboxes.begin(), m_hitboxes.end(), hitbox);
	if (itr == m_hitboxes.end()) return; // no such hitbox found
	m_hitboxes.erase(itr);
}

void dae::CollisionManager::CheckOverlapping()
{
	for (int index = 0; index < m_hitboxes.size(); index++)
	{
		Hitbox* hitbox = m_hitboxes[index];

		for (int indexOther = index; indexOther < m_hitboxes.size(); indexOther++)
		{
			Hitbox* hitboxOther = m_hitboxes[indexOther];
			if (hitboxOther == hitbox) continue; // don't calculate isOverlapping with itself

			if (hitbox->IsHit(*hitboxOther))
			{
				// Call collision on all components
				GameObject* thisObj = hitbox->GetGameObject();
				GameObject* otherObj = hitboxOther->GetGameObject();

				thisObj->OnCollision(otherObj);
				otherObj->OnCollision(thisObj);
			}
		}
	}
}
