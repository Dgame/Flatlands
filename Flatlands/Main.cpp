#include <SGL\Window\Event.hpp>
#include "InitScreen.hpp"
#include "LoseScreen.hpp"
#include "World.hpp"
#include "StateMachine.hpp"

int main() {
	sgl::Window wnd(512, 512, "Flatland");
	wnd.framerateLimit = 10;

	InitScreen init(wnd);
	LoseScreen lose(wnd);
	World world(wnd);

	StateMachine sm;
	sm.registerState(State::Init, &init);
	sm.registerState(State::Lose, &lose);
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
							world.getPlayer()->prepareRoll(Direction::Left);
						} else if (event.keyboard.key == sgl::Keyboard::Code::Right) {
							world.getPlayer()->prepareRoll(Direction::Right);
						} else if (event.keyboard.key == sgl::Keyboard::Code::Up)
							world.revertGravity(Gravity::Up);
						else if (event.keyboard.key == sgl::Keyboard::Code::Down)
							world.revertGravity(Gravity::Down);
						else if (event.keyboard.key == sgl::Keyboard::Code::Space)
							world.getPlayer()->isJumping = true;
					} else
						sm.setState(State::Game);
					break;
			}
		}

		sm.execute();

		wnd.display();
	}
}