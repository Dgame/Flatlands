#ifndef PAUSE_SCREEN_HPP
#define PAUSE_SCREEN_HPP

#include <memory>
#include "SpriteScreen.hpp"

class PauseScreen : public SpriteScreen {
public:
	explicit PauseScreen(const sgl::Window& wnd);
};

#endif