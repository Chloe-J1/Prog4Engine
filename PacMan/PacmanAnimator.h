#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/IObserver.h"
namespace dae
{
	class SpriteComponent;
}
namespace pacman
{
	class PacmanAnimator final : public dae::Component, public dae::IObserver
	{
	public:
		PacmanAnimator(dae::GameObject* owner);
		~PacmanAnimator();
		PacmanAnimator(const PacmanAnimator& other) = delete;
		PacmanAnimator(PacmanAnimator&& other) = delete;
		PacmanAnimator& operator=(const PacmanAnimator& other) = delete;
		PacmanAnimator& operator=(PacmanAnimator&& other) = delete;

		virtual void Notify(dae::GameObject* sender, const dae::Event& event);
	private:
		dae::SpriteComponent* m_spriteComp;
	};
}