#ifndef TRANSITION_MANAGER_HPP
#define TRANSITION_MANAGER_HPP

#include <stack>
#include <memory>
#include "Transition.hpp"

class TransitionManager final {
private:
	std::stack<std::unique_ptr<Transition>> _stack;

public:
	bool isRunning() const {
		return !_stack.empty();
	}

	void push(Transition* tcp) {
		_stack.push(std::unique_ptr<Transition>(tcp));
	}

	void execute();
};

#endif