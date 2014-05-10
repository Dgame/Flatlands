#include "Force.hpp"
#include "Player.hpp"

const sgl::Vector2s Force::GravityForce[2] = {
	sgl::Vector2s(0, 8),
	sgl::Vector2s(0, -8)
};

const sgl::Vector2s Force::JumpForce[2] = {
	sgl::Vector2s(16, -32),
	sgl::Vector2s(16, 32)
};

Force::Force(Gravity g) : tmpGravity(GravityForce[g]), tmpJump(JumpForce[g]) {

}

void Force::executeGravity(Player* player, Gravity g) {
	if (_gravityCount == -1)
		this->tmpGravity = GravityForce[g];

	_gravityCount++;

	player->move(static_cast<sgl::Vector2f>(this->tmpGravity));
	this->tmpGravity += GravityForce[g];
}

void Force::executeJump(Player* player, Gravity g) {
	if (_jumpCount == -1) {
		this->tmpJump = JumpForce[g];
		if (player->getDir() == Direction::Left)
			this->tmpJump.x *= -1;
	}

	_jumpCount++;

	player->move(static_cast<sgl::Vector2f>(this->tmpJump));
	this->tmpJump += GravityForce[g];
}

Gravity Force::ReverseGravity(Gravity g) {
	switch (g) {
		case Gravity::Down:
			g = Gravity::Up;
			break;
		case Gravity::Up:
			g = Gravity::Down;
			break;
	}

	return g;
}