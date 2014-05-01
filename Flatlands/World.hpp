#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <memory>
#include "Screen.hpp"
#include "Player.hpp"
#include "Ground.hpp"
#include "Force.hpp"
#include "Level.hpp"

class StateMachine;

class World : public Screen {
private:
	std::vector<std::unique_ptr<Ground>> _grounds;

	Player _player;
	Force _force;
	LevelManager _level;

	Gravity _gravity = Gravity::Down;

	sgl::Vector2s* _getPlayerOffset() {
		return _player.isJumping ? &_force.tmpJump : &_force.tmpGravity;
	}

	void _abortForce();
	void _handleGroundCollision();
	bool _detectGroundCollision(const Ground** gp) const;
	bool _detectTopCollision() const;
	bool _detectBorderCollision() const;

public:
	explicit World(const sgl::Window& wnd);
	void setup() override;
	void execute(StateMachine* sm) override;

	void revertGravity(Gravity current);

	Player* getPlayer() {
		return &_player;
	}
};

#endif