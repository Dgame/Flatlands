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
	if (!_stack.empty())
		_stack.pop();

	_stack.top().screen->setup();
	this->execute();
}

const State StateMachine::getCurrentState() const {
	if (_stack.empty())
		return State::None;
	return _stack.top().state;
}

void StateMachine::execute() {
	_stack.top().screen->execute(this);
}