#ifndef INTRO_SCREEN_HPP
#define INTRO_SCREEN_HPP

#include <vector>
#include "Screen.hpp"
#include "FadeTransition.hpp"
#include "TransitionManager.hpp"
#include "StateMachine.hpp"


class IntroScreen : public Screen {
private:
	static const std::vector<std::string> Pages;

	sgl::Sprite _curSprite;
	sgl::Texture _curTex;

	sgl::Sprite _oldSprite;
	sgl::Texture _oldTex;

	uint8 _pageNr = 0;
	uint32 _ticks = 0;

public:
	explicit IntroScreen(const sgl::Window& wnd);

	void load(TransitionManager* tm);
	void reload(TransitionManager* tm);
	void leave(TransitionManager* tm);
	void review(TransitionManager* tm, StateMachine* sm);
	void render(bool myTurn) const;
};

#endif