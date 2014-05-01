#include "InitScreen.hpp"
#include "StateMachine.hpp"

InitScreen::InitScreen(const sgl::Window& wnd) : Screen(wnd), _tex(sgl::Texture::LoadFromFile("Images/wiki.png")), _init(_tex) {

}

void InitScreen::execute(StateMachine*) {
	_wnd.draw(_init);
}