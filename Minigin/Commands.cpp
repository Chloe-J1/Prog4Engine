#include "Commands.h"
#include "GameObject.h"
#include "MoveComponent.h"

void dae::Jump::Execute()
{
	MoveComponent* move = GetGameObject()->GetComponent<MoveComponent>();
	if (move)
		move->Move(5.f, glm::vec3(1,0,0));
}
