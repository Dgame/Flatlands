#ifndef TRANSITION_HPP
#define TRANSITION_HPP

namespace sgl {
	class Window;
}

class Transition {
protected:
	const sgl::Window* _wnd;

public:
	explicit Transition(const sgl::Window* wnd);
	virtual bool execute() = 0;
};

#endif