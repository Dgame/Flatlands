#include "World.hpp"
#include "StateMachine.hpp"

World::World(const sgl::Window& wnd) : Screen(wnd), _force(_gravity) {
	_level.loadNextLevel(_grounds);
	this->setup();
}

void World::_detectGroundCollision() {
	bool collide = false;

	if (_player.getVertex(_gravity, Direction::Left).y <= 0) {
		collide = true;
	} else {
		for (const std::unique_ptr<Ground>& g : _grounds) {
			if (_player.collideWithGround(_gravity, g.get(), &_force.tmpGravity)) {
				collide = true;

				break;
			}
		}
	}

	if (collide) {
		printf("Kollision\n");
		_force.abortForce();
		_player.isOnGround = true;
	}
}

void World::_detectBorderCollision() {

}

void World::setup() {
	_player.init(_level.getCurrentLevel().startPosition);
}

void World::execute(StateMachine* sm) {
	if (!_player.isOnGround) {
		_force.executeGravity(&_player, _gravity);
		_detectGroundCollision();
	} else if (_player.isJumping) {
		_force.executeJump(&_player, _gravity);
		_detectGroundCollision();
	} else if (_player.isOnGround && _player.isMoving()) {
		_player.executeRoll(_gravity);
		_player.isOnGround = false;
		_detectGroundCollision();
	}

	for (const std::unique_ptr<Ground>& g : _grounds) {
		_wnd.draw(*g);
	}

	_wnd.draw(_player);

	if (_player.getVertex(_gravity, Direction::Left).y > _wnd.height())
		sm->setState(State::Lose);
}

void World::revertGravity(Gravity too) {
	if (too == _gravity || !_player.isOnGround || _player.isJumping)
		return;

	_gravity = Force::ReverseGravity(_gravity);
	_player.isOnGround = false;
	_detectGroundCollision();
}