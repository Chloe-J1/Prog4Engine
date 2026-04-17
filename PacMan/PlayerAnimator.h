#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/SpriteComponent.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/Observer.h"
#include "../Minigin/EventQueue.h"
#include "Events.h"
namespace pacman
{
	class PlayerAnimator : public dae::Component, public dae::Observer
	{
	public:
		PlayerAnimator(dae::GameObject* owner, dae::SpriteComponent* spriteComp) :
			dae::Component(owner),
			m_sprite{ spriteComp }
		{
			dae::EventQueue::GetInstance().AddObserver(this);
		}
		~PlayerAnimator()
		{
			dae::EventQueue::GetInstance().RemoveObserver(this);
		}
		PlayerAnimator(const PlayerAnimator& other) = delete;
		PlayerAnimator(PlayerAnimator&& other) = delete;
		PlayerAnimator& operator=(const PlayerAnimator& other) = delete;
		PlayerAnimator& operator=(PlayerAnimator&& other) = delete;

		virtual void Notify(dae::GameObject* gameObject, const dae::Event& event)
		{
			if (event.id == "DIRECTION_CHANGED" && gameObject == GetGameObject())// Only update sprite for your character
			{
				DirectionChangedArg* arg = static_cast<DirectionChangedArg*>(event.arg.get());
				if (arg->direction.x == 1) // right
				{
					m_sprite->SetRow(0);
				}
				else if (arg->direction.x == -1) // left
				{
					m_sprite->SetRow(1);
				}
				else if (arg->direction.y == -1) // up
				{
					m_sprite->SetRow(2);
				}
				else  // down
				{
					m_sprite->SetRow(3);
				}
			}
		}
	private:
		dae::SpriteComponent* m_sprite;
	};
}
