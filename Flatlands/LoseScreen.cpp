#include "LoseScreen.hpp"
#include "StateMachine.hpp"

LoseScreen::LoseScreen(const sgl::Window& wnd) : SpriteScreen(wnd, "Images/lose.png") {
	_sprite.position.set(0, (wnd.height() / 2) - _tex.height());
}

void LoseScreen::review(TransitionManager*, StateMachine* sm) {
	if ((_counter + 2000) < sgl::Clock::GetTicks())
		sm->reloadPreviousState();
}

void LoseScreen::load(TransitionManager*) {
	_counter = sgl::Clock::GetTicks();
}