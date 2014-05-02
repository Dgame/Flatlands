#include "World.hpp"
#include "StateMachine.hpp"

World::World(const sgl::Window& wnd) : Screen(wnd), _force(_gravity) {
	_level.loadNextLevel(_grounds);
	this->setup();
}

void World::_abortForce() {
	_force.abort();
	_player.isOnGround = true;
	_player.isJumping = false;
}

void World::_handleGroundCollision() {
	if (!_player.isOnGround) {
		const Ground* gp = nullptr;
		Collision col = Collision::No;

		if (_detectGroundCollision(&gp, &col)) {
			if (col == Collision::Edge && _player.isJumping) {
				_abortForce();
				_player.isOnGround = false;
			} else if (col == Collision::Yes)
				_abortForce();
		} else if (gp != nullptr) {
			const sgl::Vertex& gLeft = gp->getVertex(Force::ReverseGravity(_gravity), Direction::Left);
			_getPlayerOffset()->y = gLeft.y - _player.getVertex(_gravity, Direction::Left).y;
		}
	}
}

bool World::_detectGroundCollision(const Ground** gp, Collision* colp) const {
	const sgl::Vector2s& offset = _player.isJumping ? _force.tmpJump : _force.tmpGravity;

	if (_player.getVertex(_gravity, Direction::Left).y <= 0)
		return true;

	for (const std::unique_ptr<Ground>& g : _grounds) {
		Collision col = _player.collideWithGround(_gravity, g.get(), offset);

		if (colp != nullptr)
			*colp = col;

		if (col == Collision::Next)
			*gp = g.get();
		else if (col != Collision::No)
			return true;
	}

	return false;
}

bool World::_detectBorderCollision() const {
	const sgl::Vertex& v = _player.getVertex(_gravity, _player.getDir());

	return v.x <= 0 || v.x >= _wnd.width();
}

void World::setup() {
	_player.init(_level.getCurrentLevel().startPosition);
}

void World::execute(StateMachine* sm) {
	if (!_player.isOnGround && !_player.isJumping) {
		_force.executeGravity(&_player, _gravity);
	} else if (_player.isJumping) {
		_force.executeJump(&_player, _gravity);
		_player.isOnGround = false;

		if (_detectBorderCollision())
			_force.tmpJump.x = 0;
	} else if (_player.isOnGround && _player.isRolling()) {
		if (_detectBorderCollision())
			_player.abortRoll();
		else
			_player.executeRoll(_gravity);

		_player.isOnGround = false;
	}

	if (!_player.isOnGround)
		_handleGroundCollision();

	for (const std::unique_ptr<Ground>& g : _grounds) {
		_wnd.draw(*g);
	}

	_wnd.draw(_player);

	if (_player.getVertex(_gravity, Direction::Left).y > _wnd.height()) {
		_force.abort();

		sm->setState(State::Lose);
	}
}

void World::revertGravity(Gravity too) {
	if (too == _gravity || !_player.isOnGround || _player.isJumping)
		return;

	_gravity = Force::ReverseGravity(_gravity);

	_player.isOnGround = false;
	_handleGroundCollision();
}