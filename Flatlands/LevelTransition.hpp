#ifndef LEVLE_TRANSITION_HPP
#define LEVEL_TRANSITION_HPP

#include "Transition.hpp"

class Player;
class Ground;
class Area;

class LevelTransition : public Transition {
private:
	Player* _player;
	const Ground* _ground;
	Area* _area;

public:
	explicit LevelTransition(const sgl::Window* wnd, Area* area, Player* player, const Ground* ground);
	bool execute() override;
};

#endif