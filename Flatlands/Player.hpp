#ifndef PLAYER_HPP
#define PLAYER_HPP

#define PlayerSize 48
#define PlayerMoveTime 6
#define PlayerMoveStep (PlayerSize / PlayerMoveTime)
#define PlayerMoveAngle (90 / PlayerMoveTime)

#include <SGL\Window\Window.hpp>
#include "Area.hpp"

class Ground;

class Player final : public Area {
public:
	bool isOnGround = false;
	bool isJumping = false;

	explicit Player();

	void init(const sgl::Vector2s& position);

	void abortRoll() {
		_moveCounter = -1;
		sgl::Shape::setRotation(0);
	}

	void prepareRoll(Direction dir);
	bool executeRoll(Gravity g);
	bool collideWithGround(Gravity g, const Ground* ground, sgl::Vector2s* offset) const;
	bool collideWithBorder(Gravity g, const sgl::Window& wnd, sgl::Vector2s* offset) const;
};

#endif