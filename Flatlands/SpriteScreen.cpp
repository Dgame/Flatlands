#include "SpriteScreen.hpp"

SpriteScreen::SpriteScreen(const sgl::Window& wnd, const std::string& filename) : Screen(wnd), _img(filename), _sprite(_img) {

}