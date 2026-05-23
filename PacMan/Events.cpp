#include "Events.h"

pacman::ScoreArg::ScoreArg(int _score):
	score{_score}
{
}

pacman::UpdateHealthArg::UpdateHealthArg(int _health) :
	health{ _health }
{
}

pacman::DirectionChangedArg::DirectionChangedArg(glm::vec2 _direction) :
	direction{ _direction }
{
}

pacman::GhostDiedArg::GhostDiedArg(dae::GameObject* _ghost) :
	ghost{ _ghost }
{
}