#include "World.hpp"
#include "LevelTransition.hpp"
#include "StateMachine.hpp"

World::World(const sgl::Window& wnd) : Screen(wnd), _force(_gravity) {

}

void World::_checkWin(Ground* g) {
	if (g != nullptr && g->isTarget()) {
		_gtarget = g;
		_won = Won::WIP;
	}
}

bool World::_detectTopBorderCollision() {
	if (_gravity != Gravity::Up || _player.isOnGround)
		return false;

	const sgl::Vertex& vp = _player.getVertex(_gravity, Direction::Left);

	if (vp.y <= 0)
		return true;
	else if ((vp.y + _getPlayerOffset()->y) <= 0)
		_getPlayerOffset()->y = 0 - vp.y;

	return false;
}

void World::_handleGroundCollision() {
	if (!_player.isOnGround) {
		Ground* gp = nullptr;
		Collision col = Collision::No;

		if (_detectGroundCollision(&gp, &col)) {
			if (col == Collision::Edge && _player.isJumping) {
				_player.isOnGround = false;
				_player.isJumping = false;
				_force.reset();
			} else if (col == Collision::Yes) {
				_player.isOnGround = true;
				_player.isJumping = false;
				_force.reset();
			}

			_checkWin(gp);
		} else if (col == Collision::Next) {
			const sgl::Vertex& gLeft = gp->getVertex(Force::ReverseGravity(_gravity), Direction::Left);
			_getPlayerOffset()->y = gLeft.y - _player.getVertex(_gravity, Direction::Left).y;
		}
	}
}

bool World::_detectGroundCollision(Ground** gp, Collision* colp) const {
	const sgl::Vector2s& offset = _player.isJumping ? _force.tmpJump : _force.tmpGravity;

	for (const std::unique_ptr<Ground>& g : _grounds) {
		Collision col = _player.collideWithGround(_gravity, g.get(), offset);

		if (col != Collision::No) {
			*colp = col;
			*gp = g.get();

			/// Ausnahmen
			if (col == Collision::Next)
				continue;

			return true;
		}
	}

	return false;
}

bool World::_detectSideBorderCollision() const {
	const sgl::Vertex& v = _player.getVertex(_gravity, _player.getDir());

	return v.x <= 0 || v.x >= _wnd.width();
}

void World::load(TransitionManager*) {
	_player.isOnGround = false;
	_player.isJumping = false;
	_force.reset();

	_gtarget = nullptr;
	_won = Won::No;

	if (_level.loadNextLevel(_grounds))
		_player.init(_level.getCurrentLevel().startPosition);
	else
		_won = Won::All;
}

void World::reload(TransitionManager*) {
	_player.isOnGround = false;
	_player.isJumping = false;
	_force.reset();

	_player.init(_level.getCurrentLevel().startPosition);
}

void World::review(TransitionManager* tm, StateMachine* sm) {
	if (_won == Won::Yes)
		sm->loadCurrentState();
	else if (_won == Won::All)
		sm->setState(State::Won);
	else if (_won == Won::WIP && _gtarget != nullptr) {
		_won = Won::Yes;
		tm->push(new LevelTransition(&_wnd, &_player, _gtarget));
	} else if (_player.getVertex(_gravity, Direction::Left).y > _wnd.height()) { /// Out of window?
		sm->setState(State::Lose);
	}
}

void World::execute(const sgl::Event&) {
	if (_player.isJumping) {
		_force.executeJump(&_player, _gravity);
		_player.isOnGround = false;

		if (_detectSideBorderCollision())
			_force.tmpJump.x = 0;
	} else if (!_player.isOnGround) {
		_force.executeGravity(&_player, _gravity);
	} else if (_player.isRolling()) {
		if (_detectSideBorderCollision())
			_player.abortRoll();
		else
			_player.executeRoll(_gravity);

		_player.isOnGround = false;
	}

	if (!_player.isOnGround) {
		if (_detectTopBorderCollision()) {
			_player.isJumping = false;
			_player.isOnGround = true;
			_force.reset();
		} else
			_handleGroundCollision();
	}
}

void World::render(bool) const {
	for (const std::unique_ptr<Ground>& g : _grounds) {
		_wnd.draw(*g);
	}

	_wnd.draw(_player);
}

void World::revertGravity(Gravity too) {
	if (too == _gravity || !_player.isOnGround || _player.isJumping)
		return;

	_gravity = Force::ReverseGravity(_gravity);

	_player.isOnGround = false;
	_handleGroundCollision();
}