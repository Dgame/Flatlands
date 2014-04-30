#ifndef LOSE_SCREEN_HPP
#define LOSE_SCREEN_HPP

#include <memory>
#include <SGL\Graphic\Sprite.hpp>
#include <SGL\System\Clock.hpp>
#include "Screen.hpp"

class StateMachine;

class LoseScreen : public Screen {
private:
	sgl::Texture _tex;
	sgl::Sprite _lose;

	uint32 _counter = 0;

public:
	explicit LoseScreen(const sgl::Window& wnd);
	void execute(StateMachine* sm) override;
};

#endif