#include "Events.h"

pacman::ScoreArg::ScoreArg(int _score, dae::GameObject* _sender):
	score{_score},
	sender{_sender}
{
}

pacman::UpdateHealthArg::UpdateHealthArg(int _health, dae::GameObject* _sender) :
	health{ _health },
	sender{_sender}
{
}

pacman::DirectionChangedArg::DirectionChangedArg(glm::vec2 _direction, dae::GameObject* _sender) :
	direction{ _direction },
	sender{_sender}
{
}

pacman::GhostDiedArg::GhostDiedArg(dae::GameObject* _ghost, dae::GameObject* _killer) :
	ghost{ _ghost },
	killer{_killer}
{
}

pacman::SenderArg::SenderArg(dae::GameObject* _sender):
	sender{_sender}
{
}
