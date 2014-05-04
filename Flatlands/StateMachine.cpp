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

		_stack.push(CurrentScreen(it->second, state));

		this->setupCurrentState();
	}
}

void StateMachine::setupCurrentState() {
	_stack.top().screen->setup(&_transitions);
}

void StateMachine::resetCurrentState() {
	_stack.top().screen->reset(&_transitions);
}

void StateMachine::popCurrentState() {
	if (!_stack.empty()) {
		_stack.top().screen->leave(&_transitions);
		_stack.pop();
	}
}

void StateMachine::resetPreviousState() {
	this->popCurrentState();
	this->resetCurrentState();
}

void StateMachine::execute() {
	Screen* screen = _stack.top().screen;

	if (!_transitions.isRunning())
		screen->review(&_transitions);

	if (!_transitions.isRunning())
		screen->execute(this);
	else
		_transitions.execute();

	screen->render();
}