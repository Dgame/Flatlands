#ifndef INIT_SCREEN_HPP
#define INIT_SCREEN_HPP

#include <memory>
#include "SpriteScreen.hpp"

class InitScreen : public SpriteScreen {
public:
	explicit InitScreen(const sgl::Window& wnd);

	void leave(TransitionManager* tm) override;
};

#endif