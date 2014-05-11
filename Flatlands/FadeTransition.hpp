#ifndef FADE_TRANSITION_HPP
#define FADE_TRANSITION_HPP

#include <SGL/Graphic/Sprite.hpp>
#include <SGL/Graphic/Blend.hpp>
#include <SGL/Window/Window.hpp>
#include "Transition.hpp"

class FadeTransition : public Transition {
private:
	const bool _backwards;
	sgl::Blend _blend;
	const sgl::Sprite* _sprite;

public:
	explicit FadeTransition(const sgl::Window* wnd, const sgl::Sprite* sp, bool backwards);
	bool execute();
};

#endif