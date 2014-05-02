#include "LoseScreen.hpp"
#include "StateMachine.hpp"

LoseScreen::LoseScreen(const sgl::Window& wnd) : SpriteScreen(wnd, "Images/lose.png") {
	_sprite.position.set(0, (wnd.height() / 2) - _tex.height());
}

void LoseScreen::execute(StateMachine* sm) {
	if (_counter == 0)
		_counter = sgl::Clock::GetTicks();

	if ((_counter + 4000) >= sgl::Clock::GetTicks()) {
		_wnd.draw(_sprite);
	} else {
		_counter = 0;
		sm->setPreviousState();
	}
}