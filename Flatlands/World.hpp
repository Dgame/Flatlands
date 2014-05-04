#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <memory>
#include "Screen.hpp"
#include "Player.hpp"
#include "Ground.hpp"
#include "Force.hpp"
#include "Level.hpp"

enum class Won {
	No,
	WIP,
	Yes,
	All
};

class World : public Screen {
private:
	std::vector<std::unique_ptr<Ground>> _grounds;

	Player _player;
	Force _force;
	LevelManager _level;

	Gravity _gravity = Gravity::Down;
	Won _won = Won::No;
	const Ground* _gtarget = nullptr;

	sgl::Vector2s* _getPlayerOffset() {
		return _player.isJumping ? &_force.tmpJump : &_force.tmpGravity;
	}

	void _checkWin(const Ground* g);
	void _abortForce();
	bool _handleBorderCollision();
	void _handleGroundCollision();
	bool _detectGroundCollision(const Ground** gp, Collision* colp) const;
	bool _detectBorderCollision() const;

public:
	explicit World(const sgl::Window& wnd);
	void setup(TransitionManager*) override;
	void review(TransitionManager* tm) override;
	void execute(StateMachine* sm) override;

	void revertGravity(Gravity current);

	Player* getPlayer() {
		return &_player;
	}
};

#endif