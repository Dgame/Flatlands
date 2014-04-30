#include "LoseScreen.hpp"
#include "StateMachine.hpp"

LoseScreen::LoseScreen(const sgl::Window& wnd) : Screen(wnd), _tex(sgl::Texture::LoadFromFile("Images/lose.png")), _lose(_tex) {
	_lose.position.set(0, (wnd.height() / 2) - _tex.height());
}

void LoseScreen::execute(StateMachine* sm) {
	if (_counter == 0)
		_counter = sgl::Clock::GetTicks();

	if ((_counter + 4000) >= sgl::Clock::GetTicks()) {
		_wnd.draw(_lose);
	} else {
		_counter = 0;
		sm->setPreviousState();
	}
}