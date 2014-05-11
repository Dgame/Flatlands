#include "InitTransition.hpp"
#include <SGL/Graphic/Sprite.hpp>
#include <SGL/Window/Window.hpp>

InitTransition::InitTransition(const sgl::Window* wnd, sgl::Sprite* sprite) : Transition(wnd), _sprite(sprite) {

}

bool InitTransition::execute() {
	_sprite->position.move(0, 50);
	_wnd->draw(*_sprite);

	return _sprite->position.y <= _wnd->height();
}