#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SGL\Window\Window.hpp>

class TransitionManager;
class StateMachine;

class Screen {
protected:
	const sgl::Window& _wnd;

public:
	explicit Screen(const sgl::Window& wnd);

	virtual void execute() {

	}

	virtual void render() const = 0;

	virtual void load(TransitionManager*) {

	}

	virtual void reload(TransitionManager*) {

	}

	virtual void review(TransitionManager*, StateMachine*) {

	}

	virtual void leave(TransitionManager*) {

	}
};

#endif