#include "IntroScreen.hpp"

const std::vector<std::string> IntroScreen::Pages = {
	"images/intro_1.png",
	"images/intro_2.png"
};

IntroScreen::IntroScreen(const sgl::Window& wnd) : Screen(wnd) {
	
}

void IntroScreen::load(TransitionManager* tm) {
	printf("Load Page: %s\n", Pages[_pageNr].c_str());

	sgl::Surface s = sgl::Surface(Pages[_pageNr]);
	_curTex.loadFrom(s);
	_curSprite.setTexture(_curTex);
	// Fade in
	tm->push(new FadeTransition(&_wnd, &_curSprite, false));

	_ticks = sgl::Clock::GetTicks();
}

void IntroScreen::reload(TransitionManager* tm) {
	_pageNr++;

	printf("Reload Page: %s\n", Pages[_pageNr].c_str());

	sgl::Surface s = sgl::Surface(Pages[_pageNr]);
	_curTex.loadFrom(s);
	_curSprite.setTexture(_curTex);

	// Fade in
	tm->push(new FadeTransition(&_wnd, &_curSprite, false));

	_ticks = sgl::Clock::GetTicks();
}

void IntroScreen::leave(TransitionManager* tm) {
	// Fade out
	tm->push(new FadeTransition(&_wnd, &_curSprite, true));
}

void IntroScreen::review(TransitionManager* tm, StateMachine* sm) {
	if ((_ticks + 4000) < sgl::Clock::GetTicks()) {
		if (_pageNr >= Pages.size() - 1)
			sm->setState(State::Game);
		else {
			std::unique_ptr<uint32> pixel = _curTex.pixels();
			_oldTex.loadFromMemory(pixel.get(), _curTex.width(), _curTex.height(), _curTex.format()); // TODO
			_oldSprite.setTexture(_oldTex);
			// Fade out
			tm->push(new FadeTransition(&_wnd, &_oldSprite, true));
			sm->reloadCurrentState();
		}
	}
}

void IntroScreen::render(bool myTurn) const {
	if (myTurn) {
		_wnd.draw(_curSprite);
	}
}