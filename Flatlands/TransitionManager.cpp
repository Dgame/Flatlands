#include "TransitionManager.hpp"

void TransitionManager::execute() {
	if (_list.empty())
		return;

	if (!_list.front()->execute())
		_list.pop_front();
}