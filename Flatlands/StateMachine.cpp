#include "StateMachine.hpp"
#include "Screen.hpp"

CurrentScreen::CurrentScreen(Screen* pscreen, State pstate) : screen(pscreen), state(pstate) {

}

void StateMachine::setState(State state) {
	if (this->getCurrentState() == state)
		return;

	std::map<State, Screen*>::iterator it = _screens.find(state);
	if (it != _screens.end())
		_stack.push(CurrentScreen(it->second, state));
}

void StateMachine::setPreviousState() {
	if (!_stack.empty()) {
		_stack.top().screen->leave();
		_stack.pop();
	}

	_stack.top().screen->setup();
	//this->execute();
}

void StateMachine::execute() {
	_stack.top().screen->execute(this);
}