#include "FadeTransition.hpp"

FadeTransition::FadeTransition(const sgl::Window* wnd, const sgl::Sprite* sp, bool backwards) : Transition(wnd), _sprite(sp),
_blend(sgl::Blend::Factor::One, sgl::Blend::Factor::OneMinusSrcAlpha), _backwards(backwards) {
	if (!backwards)
		_blend.color = sgl::Color::White.withTransparency(0);
}

bool FadeTransition::execute() {
	if (_backwards)
		_blend.color.alpha -= 25;
	else
		_blend.color.alpha += 25;

	printf("Fade Transition with %d\n", _blend.color.alpha);

	_wnd->draw(*_sprite, sgl::DrawOptions(&_blend));

	if (_backwards)
		return _blend.color.alpha > 25;

	return _blend.color.alpha < 250;
}