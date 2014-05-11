#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <map>
#include <stack>
#include <SGL\Window\Event.hpp>
#include "TransitionManager.hpp"

class Screen;

enum class State : short {
	None,
	Won,
	Lose,
	Init,
	Intro,
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
	void loadCurrentState();
	void reloadCurrentState();
	void reloadPreviousState();

	const State getCurrentState() const {
		if (_stack.empty())
			return State::None;

		return _stack.top().state;
	}

	void execute(const sgl::Event& event);
};

#endif