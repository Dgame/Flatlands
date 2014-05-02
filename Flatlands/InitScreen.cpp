#include "InitScreen.hpp"
#include "TransitionManager.hpp"
#include "InitTransition.hpp"

InitScreen::InitScreen(const sgl::Window& wnd) : SpriteScreen(wnd, "Images/init.png") {

}

void InitScreen::leave(TransitionManager* tm) {
	tm->push(new InitTransition(&_wnd, &_sprite));
}