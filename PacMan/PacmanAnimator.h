#pragma once
#include "../Minigin/Component.h"
#include "../Minigin/IEventHandler.h"
namespace dae
{
	class SpriteComponent;
}
namespace pacman
{
	class PacmanAnimator final : public dae::Component, public dae::IEventHandler
	{
	public:
		PacmanAnimator(dae::GameObject* owner);
		~PacmanAnimator();
		PacmanAnimator(const PacmanAnimator& other) = delete;
		PacmanAnimator(PacmanAnimator&& other) = delete;
		PacmanAnimator& operator=(const PacmanAnimator& other) = delete;
		PacmanAnimator& operator=(PacmanAnimator&& other) = delete;

		void Notify(const dae::Event& event);
	private:
		dae::SpriteComponent* m_spriteComp;
	};
}