#include "World.hpp"
#include "LevelTransition.hpp"
#include "StateMachine.hpp"

World::World(const sgl::Window& wnd) : Screen(wnd), _force(_gravity) {
	
}

void World::_checkWin(const Ground* g) {
	if (g != nullptr && g->isTarget()) {
		const sgl::Vertex& lv = _player.getVertex(_gravity, Direction::Left);
		const sgl::Vertex& rv = _player.getVertex(_gravity, Direction::Right);

		if (g->targetRect->contains(lv.x, lv.y + 4) && g->targetRect->contains(rv.x, rv.y + 4)) {
			_gtarget = g;
			_won = Won::WIP;
		}
	}
}

void World::_abortForce() {
	_force.abort();
	_player.isOnGround = true;
	_player.isJumping = false;
}

bool World::_handleBorderCollision() {
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
		if (_handleBorderCollision())
			return _abortForce();

		const Ground* gp = nullptr;
		Collision col = Collision::No;

		if (_detectGroundCollision(&gp, &col)) {
			if (col == Collision::Edge && _player.isJumping) {
				_abortForce();
				_player.isOnGround = false;
			} else if (col == Collision::Yes)
				_abortForce();

			_checkWin(gp);
		} else if (gp != nullptr) {
			const sgl::Vertex& gLeft = gp->getVertex(Force::ReverseGravity(_gravity), Direction::Left);
			_getPlayerOffset()->y = gLeft.y - _player.getVertex(_gravity, Direction::Left).y;
		}
	}
}

bool World::_detectGroundCollision(const Ground** gp, Collision* colp) const {
	const sgl::Vector2s& offset = _player.isJumping ? _force.tmpJump : _force.tmpGravity;

	for (const std::unique_ptr<Ground>& g : _grounds) {
		Collision col = _player.collideWithGround(_gravity, g.get(), offset);

		*colp = col;

		if (col != Collision::No) {
			*gp = g.get();

			/// Ausnahmen
			if (col == Collision::Next)
				continue;

			return true;
		}
	}

	return false;
}

bool World::_detectBorderCollision() const {
	const sgl::Vertex& v = _player.getVertex(_gravity, _player.getDir());

	return v.x <= 0 || v.x >= _wnd.width();
}

void World::setup(TransitionManager*) {
	_gtarget = nullptr;
	_won = Won::No;

	if (_level.loadNextLevel(_grounds))
		_player.init(_level.getCurrentLevel().startPosition);
	else
		_won = Won::All;
}

void World::review(TransitionManager* tm) {
	if (_won == Won::WIP && _gtarget != nullptr) {
		_won = Won::Yes;
		tm->push(new LevelTransition(&_wnd, _gtarget->target.get(), &_player, _gtarget));
	}
}

void World::execute(StateMachine* sm) {
	if (_won == Won::Yes)
		return sm->resetState();
	else if (_won == Won::All)
		return sm->setState(State::Won);

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

	/// Out of window?
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