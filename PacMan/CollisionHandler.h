#pragma once
#include "Component.h"
#include "Observer.h"
#include "GameObject.h"
#include "EventQueue.h"
#include "Pellets.h"
namespace pacman
{
	class CollisionHandler final : public dae::Component, public dae::Observer
	{
    public:
        CollisionHandler(dae::GameObject* owner):
            Component(owner)
        {
            dae::EventQueue::GetInstance().AddObserver(this);
        }
        ~CollisionHandler() override 
        {
            dae::EventQueue::GetInstance().RemoveObserver(this);
        }

        void Notify(dae::GameObject* sender, const Event& event) override
        {
            if (event.id != EventId::HIT) return;

            CollisionEvent* collision = dynamic_cast<CollisionEvent*>(event.args[0].get());
            if (!collision) return;
            dae::GameObject* other = collision->other;

            if (/*sender->GetComponent<PlayerComponent>() != nullptr &&*/ other->GetComponent<dae::BasePellet>() != nullptr)
            {
                Event scoreEvent{ EventId::PICKUP_PELLET };
                dae::EventQueue::GetInstance().Invoke(std::move(scoreEvent), sender);
            }
        }
	};
}
