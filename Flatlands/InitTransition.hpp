#ifndef INIT_TRANSITION_HPP
#define INIT_TRANSITION_HPP

#include "Transition.hpp"

namespace sgl {
	class Sprite;
}

class InitTransition : public Transition {
private:
	sgl::Sprite* _sprite;

public:
	explicit InitTransition(const sgl::Window* wnd, sgl::Sprite* sprite);
	bool execute();
};

#endif