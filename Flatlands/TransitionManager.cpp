#include "TransitionManager.hpp"

void TransitionManager::execute() {
	if (_stack.empty())
		return;

	if (_stack.top()->execute())
		_stack.pop();
}