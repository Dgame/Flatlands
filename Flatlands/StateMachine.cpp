#include "StateMachine.hpp"
#include "Screen.hpp"

CurrentScreen::CurrentScreen(Screen* pscreen, State pstate) : screen(pscreen), state(pstate) {

}

void StateMachine::setState(State state) {
	if (this->getCurrentState() == state)
		return;

	std::map<State, Screen*>::iterator it = _screens.find(state);
	if (it != _screens.end()) {
		if (!_stack.empty())
			_stack.top().screen->leave(&_transitions);

		it->second->setup(&_transitions);
		_stack.push(CurrentScreen(it->second, state));
	}
}

void StateMachine::resetState() {
	_stack.top().screen->setup(&_transitions);
}

void StateMachine::popCurrentState() {
	if (!_stack.empty()) {
		_stack.top().screen->leave(&_transitions);
		_stack.pop();
	}
}

void StateMachine::resetPreviousState() {
	this->popCurrentState();
	this->resetState();
}

void StateMachine::execute() {
	if (!_transitions.isRunning()) {
		Screen* screen = _stack.top().screen;

		screen->review(&_transitions);

		if (!_transitions.isRunning())
			screen->execute(this);
	} else
		_transitions.execute();
}