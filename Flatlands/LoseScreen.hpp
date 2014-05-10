#ifndef LOSE_SCREEN_HPP
#define LOSE_SCREEN_HPP

#include <memory>
#include <SGL\System\Clock.hpp>
#include "SpriteScreen.hpp"

class LoseScreen : public SpriteScreen {
private:
	uint32 _counter = 0;

public:
	explicit LoseScreen(const sgl::Window& wnd);
	void review(TransitionManager*, StateMachine* sm) override;
	void load(TransitionManager*) override;
};

#endif