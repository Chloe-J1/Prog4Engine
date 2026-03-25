#pragma once
#include "Singleton.h"
#include "vector"
namespace dae
{
	class Hitbox;
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void AddHitbox(Hitbox* hitbox);
		void RemoveHitbox(Hitbox* hitbox);

		void CheckOverlapping();

	private:
		std::vector<Hitbox*> m_hitboxes;
	};
}