#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SGL\Window\Window.hpp>

class StateMachine;

class Screen {
protected:
	const sgl::Window& _wnd;

public:
	explicit Screen(const sgl::Window& wnd);
	virtual void execute(StateMachine* sm) = 0;

	virtual void setup() {

	}

	virtual void leave() {

	}
};

#endif