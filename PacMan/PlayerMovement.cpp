#include "PlayerMovement.h"
#include "../Minigin/GameObject.h"

pacman::PlayerMovement::PlayerMovement(dae::GameObject* owner) :
	Component(owner)
{
}

void pacman::PlayerMovement::Move(float speed, const glm::vec2& direction, float elaspedSec)
{
	GetGameObject()->AddLocalPosition(speed * direction * elaspedSec);
}
