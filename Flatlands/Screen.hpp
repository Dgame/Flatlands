#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SGL\Window\Window.hpp>
#include <SGL\Window\Event.hpp>

class TransitionManager;
class StateMachine;

class Screen {
protected:
	const sgl::Window& _wnd;

public:
	explicit Screen(const sgl::Window& wnd);

	virtual void execute(const sgl::Event&) {

	}

	virtual void render(bool myTurn) const = 0;

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