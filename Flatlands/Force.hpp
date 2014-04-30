#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include <SGL\Core\Types.hpp>
#include <SGL\Math.hpp>

class Player;

enum Gravity : short {
	Down = 0,
	Up = 1
};

class Force final {
private:
	int16 _jumpCount = -1;
	int16 _gravityCount = -1;

public:
	static const sgl::Vector2s GravityForce[2];
	static const sgl::Vector2s JumpForce[2];

	sgl::Vector2s tmpJump;
	sgl::Vector2s tmpGravity;

	explicit Force(Gravity g);

	void abort() {
		_jumpCount = -1;
		_gravityCount = -1;
	}

	static Gravity ReverseGravity(Gravity g);

	void executeGravity(Player* player, Gravity g);
	void executeJump(Player* player, Gravity g);
};

#endif