#ifndef TRANSITION_MANAGER_HPP
#define TRANSITION_MANAGER_HPP

#include <list>
#include <memory>
#include "Transition.hpp"

class TransitionManager final {
private:
	std::list<std::unique_ptr<Transition>> _list;

public:
	bool isRunning() const {
		return !_list.empty();
	}

	void push(Transition* tcp) {
		_list.push_back(std::unique_ptr<Transition>(tcp));
	}

	void execute();
};

#endif