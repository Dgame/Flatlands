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

void StateMachine::setPreviousState() {
	if (!_stack.empty()) {
		_stack.top().screen->leave(&_transitions);
		_stack.pop();
	}

	_stack.top().screen->setup(&_transitions);
}

void StateMachine::execute() {
	if (!_transitions.isRunning())
		_stack.top().screen->execute(this);
	else
		_transitions.execute();
}