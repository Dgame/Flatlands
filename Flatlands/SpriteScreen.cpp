#include "SpriteScreen.hpp"

SpriteScreen::SpriteScreen(const sgl::Window& wnd, const std::string& filename) : Screen(wnd),
_tex(sgl::Texture::LoadFromFile(filename)), _sprite(_tex) {

}