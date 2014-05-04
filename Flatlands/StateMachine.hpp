#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <map>
#include <stack>
#include "TransitionManager.hpp"

class Screen;

enum class State : short {
	None,
	Won,
	Lose,
	Init,
	Pause,
	Game
};

struct CurrentScreen {
	Screen* screen;
	const State state;

	explicit CurrentScreen(Screen* pscreen, State pstate);
};

class StateMachine final {
private:
	TransitionManager _transitions;

	std::map<State, Screen*> _screens;
	std::stack<CurrentScreen> _stack;

public:
	void registerState(State state, Screen* screen) {
		_screens[state] = screen;
	}

	void setState(State state);
	void popCurrentState();
	void resetState();
	void resetPreviousState();

	const State getCurrentState() const {
		if (_stack.empty())
			return State::None;

		return _stack.top().state;
	}

	void execute();
};

#endif