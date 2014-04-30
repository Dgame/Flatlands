#include "LoseScreen.hpp"
#include "StateMachine.hpp"

LoseScreen::LoseScreen(const sgl::Window& wnd) : Screen(wnd), _tex(sgl::Texture::LoadFromFile("Images/lose.png")), _lose(_tex) {

}

void LoseScreen::execute(StateMachine* sm) {
	_wnd.draw(_lose);
	sm->setPreviousState();
}