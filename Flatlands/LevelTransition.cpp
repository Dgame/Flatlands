#include <SGL\Graphic\Shape.hpp>
#include "LevelTransition.hpp"
#include "Ground.hpp"
#include "Player.hpp"

LevelTransition::LevelTransition(const sgl::Window* wnd, Area* area, Player* player, const Ground* ground) :
Transition(wnd), _area(area), _player(player), _ground(ground) {

}

bool LevelTransition::execute() {
	_player->move(0, 6);
	_area->move(0, 6);

	_wnd->draw(*_player);
	_wnd->draw(*_area);

	const float ty = _area->getVertex(Gravity::Down, Direction::Left).y;
	const float gy_m = _ground->getVertex(Gravity::Down, Direction::Left).y + _ground->Rect.height;

	//printf("%f -> %f = %d\n", ty, gy_m, ty > gy_m);

	return ty > gy_m;
}
