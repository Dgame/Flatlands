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

		this->loadCurrentState();
	}
}

void StateMachine::loadCurrentState() {
	_stack.top().screen->load(&_transitions);
}

void StateMachine::reloadCurrentState() {
	_stack.top().screen->reload(&_transitions);
}

void StateMachine::popCurrentState() {
	if (!_stack.empty()) {
		_stack.top().screen->leave(&_transitions);
		_stack.pop();
	}
}

void StateMachine::reloadPreviousState() {
	this->popCurrentState();
	this->reloadCurrentState();
}

void StateMachine::execute(const sgl::Event& event) {
	Screen* screen = _stack.top().screen;

	if (!_transitions.isRunning())
		screen->review(&_transitions, this);

	if (!_transitions.isRunning())
		screen->execute(event);
	else
		_transitions.execute();

	screen->render(!_transitions.isRunning());
}