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

	virtual void execute(StateMachine*) {

	}

	virtual void render() const {

	}

	virtual void load(TransitionManager*) {

	}

	virtual void reload(TransitionManager*) {

	}

	virtual void review(TransitionManager*) {

	}

	virtual void leave(TransitionManager*) {

	}
};

#endif