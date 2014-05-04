#ifndef LEVLE_TRANSITION_HPP
#define LEVEL_TRANSITION_HPP

#include "Transition.hpp"

class Player;
class Ground;

class LevelTransition : public Transition {
private:
	Player* _player;
	Ground* _ground;

public:
	explicit LevelTransition(const sgl::Window* wnd, Player* player, Ground* ground);
	bool execute() override;
};

#endif