#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <map>
#include <stack>
#include "Screen.hpp"

enum class State : short {
	None,
	Won,
	Lose,
	Init,
	Game
};

struct CurrentScreen {
	Screen* screen;
	const State state;

	explicit CurrentScreen(Screen* pscreen, State pstate);
};

class StateMachine final {
private:
	std::map<State, Screen*> _screens;
	std::stack<CurrentScreen> _stack;

public:
	void registerState(State state, Screen* screen) {
		_screens[state] = screen;
	}

	void setState(State state);
	void setPreviousState();

	const State getCurrentState() const {
		if (_stack.empty())
			return State::None;
		return _stack.top().state;
	}

	void execute() {
		_stack.top().screen->execute(this);
	}
};

#endif