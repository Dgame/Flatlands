#ifndef WIN_SCREEN_HPP
#define WIN_SCREEN_HPP

#include <memory>
#include "SpriteScreen.hpp"

class StateMachine;

class WinScreen : public SpriteScreen {
public:
	explicit WinScreen(const sgl::Window& wnd);
};

#endif