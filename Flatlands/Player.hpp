#ifndef PLAYER_HPP
#define PLAYER_HPP

#define PlayerSize 48
#define PlayerMoveTime 6
#define PlayerMoveStep (PlayerSize / PlayerMoveTime)
#define PlayerMoveAngle (90 / PlayerMoveTime)

#include <SGL\Window\Window.hpp>
#include "Area.hpp"

class Ground;

enum class Collision : short {
	No,
	Edge,
	Next,
	Yes
};

class Player final : public Area {
private:
	Direction _dir = Direction::Left;
	int8 _moveCounter = -1;

public:
	bool isOnGround = false;
	bool isJumping = false;

	explicit Player();

	void init(const sgl::Vector2s& position);

	void prepareJump() {
		if (this->isOnGround && !this->isJumping)
			this->isJumping = true;
	}

	void prepareRoll(Direction dir);
	bool executeRoll(Gravity g);

	void abortRoll() {
		_moveCounter = -1;
		sgl::Shape::setRotation(0);
	}

	bool isRolling() const {
		return _moveCounter != -1;
	}

	void setDir(Direction dir) {
		if (!this->isRolling())
			_dir = dir;
	}

	void reverseDir() {
		_dir = (_dir == Direction::Left) ? Direction::Right : Direction::Left;
	}

	Direction getDir() const {
		return _dir;
	}

	Collision collideWithGround(Gravity g, const Ground* ground, const sgl::Vector2s& offset) const;
};

#endif