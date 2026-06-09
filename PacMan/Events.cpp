#include "Events.h"

pacman::ScoreArg::ScoreArg(int _score):
	score{_score}
{
}

pacman::UpdateHealthArg::UpdateHealthArg(int _health) :
	health{ _health }
{
}

pacman::DirectionChangedArg::DirectionChangedArg(glm::vec2 _direction, dae::GameObject* _sender) :
	direction{ _direction },
	sender{_sender}
{
}

pacman::GhostDiedArg::GhostDiedArg(dae::GameObject* _ghost) :
	ghost{ _ghost }
{
}

pacman::SenderArg::SenderArg(dae::GameObject* _sender):
	sender{_sender}
{
}
