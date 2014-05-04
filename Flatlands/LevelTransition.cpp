#include <SGL\Graphic\Shape.hpp>
#include "LevelTransition.hpp"
#include "Ground.hpp"
#include "Player.hpp"

LevelTransition::LevelTransition(const sgl::Window* wnd, Player* player, Ground* ground) : Transition(wnd), _player(player), _ground(ground) {

}

bool LevelTransition::execute() {
	_player->move(0, 6);
	_ground->move(0, 6);

	_wnd->draw(*_player);

	const float ty = _ground->getVertex(Gravity::Up, Direction::Left).y;

	//printf("%f : %d = %d\n", ty, _wnd->height(), ty > _wnd->height());
	
	return ty > _wnd->height();
}
