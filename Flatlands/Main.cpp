#include <SGL\Window\Event.hpp>
#include "InitScreen.hpp"
#include "IntroScreen.hpp"
#include "LoseScreen.hpp"
#include "WinScreen.hpp"
#include "PauseScreen.hpp"
#include "World.hpp"
#include "StateMachine.hpp"

int main() {
	sgl::Window wnd(600, 500, "Flatland");
	wnd.setVerticalSync(sgl::Window::Sync::Disable);
	wnd.framerateLimit = 10;

	InitScreen init(wnd);
	IntroScreen intro(wnd);
	LoseScreen lose(wnd);
	WinScreen won(wnd);
	PauseScreen pause(wnd);
	World world(wnd);

	StateMachine sm;
	sm.registerState(State::Init, &init);
	sm.registerState(State::Intro, &intro);
	sm.registerState(State::Lose, &lose);
	sm.registerState(State::Won, &won);
	sm.registerState(State::Pause, &pause);
	sm.registerState(State::Game, &world);
	sm.setState(State::Init);

	sgl::Event event;
	while (wnd.isOpen()) {
		wnd.clear();

		while (sgl::Event::Poll(event)) {
			switch (event.type) {
				case sgl::Event::Type::Quit:
					wnd.close();
					break;
				case sgl::Event::Type::KeyDown:
					if (event.keyboard.key == sgl::Keyboard::Code::Escape)
						wnd.close();
					else if (sm.getCurrentState() == State::Game) {
						if (event.keyboard.key == sgl::Keyboard::Code::Left) {
							if (event.keyboard.mod == sgl::Keyboard::Mod::RCtrl)
								world.getPlayer()->setDir(Direction::Left);
							else
								world.getPlayer()->prepareRoll(Direction::Left);
						} else if (event.keyboard.key == sgl::Keyboard::Code::Right) {
							if (event.keyboard.mod == sgl::Keyboard::Mod::RCtrl)
								world.getPlayer()->setDir(Direction::Right);
							else
								world.getPlayer()->prepareRoll(Direction::Right);
						} else if (event.keyboard.key == sgl::Keyboard::Code::Up)
							world.revertGravity(Gravity::Up);
						else if (event.keyboard.key == sgl::Keyboard::Code::Down)
							world.revertGravity(Gravity::Down);
						else if (event.keyboard.key == sgl::Keyboard::Code::Space)
							world.getPlayer()->prepareJump();
						else if (event.keyboard.key == sgl::Keyboard::Code::Pause)
							sm.setState(State::Pause);
					} else if (sm.getCurrentState() == State::Pause)
						sm.popCurrentState();
					else if (event.keyboard.key == sgl::Keyboard::Code::Space) {
						if (sm.getCurrentState() == State::Intro)
							sm.setState(State::Game);
						else
							sm.setState(State::Intro);
					}

					break;
			}
		}

		sm.execute(event);

		wnd.display();
	}
}