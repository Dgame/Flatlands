#ifndef INIT_SCREEN_HPP
#define INIT_SCREEN_HPP

#include <memory>
#include <SGL\Graphic\Sprite.hpp>
#include "Screen.hpp"

class StateMachine;

class InitScreen : public Screen {
private:
	sgl::Texture _tex;
	sgl::Sprite _init;

public:
	explicit InitScreen(const sgl::Window& wnd);
	void execute(StateMachine*) override;
};

#endif