#include "Player.hpp"
#include "Ground.hpp"

Player::Player() : Area(sgl::Shape::Type::Quad) {

}

void Player::init(const sgl::Vector2s& position) {
	sgl::Shape::updateVertices(sgl::ShortRect(position.x, position.y, PlayerSize, PlayerSize));
	sgl::Shape::calculateCenter();
	sgl::Shape::setColor(sgl::Color::Blue);
	//sgl::Shape::fill = true;;
}

void Player::prepareRoll(Direction dir) {
	if (this->isOnGround && !this->isJumping) {
		this->setDir(dir);

		if (!this->isRolling())
			_moveCounter = 0;
	}
}

bool Player::executeRoll(Gravity g) {
	if (_moveCounter != -1) {
		float x = PlayerMoveStep;
		float angle = PlayerMoveAngle;

		if (_dir == Direction::Left)
			x *= -1;

		switch (g) {
			case Gravity::Down:
				if (_dir == Direction::Left)
					angle *= -1;
				break;
			case Gravity::Up:
				if (_dir == Direction::Right)
					angle *= -1;
				break;
		}

		sgl::Shape::move(x, 0);
		sgl::Shape::rotate(angle);

		_moveCounter++;
		if (_moveCounter >= PlayerMoveTime) {
			this->abortRoll();

			return true;
		}
	}

	return false;
}

Collision Player::collideWithGround(Gravity g, const Ground* ground, const sgl::Vector2s& offset) const {
	const sgl::Vertex& pLeft = Area::getVertex(g, Direction::Left);
	const sgl::Vector2f left = pLeft.getPosition();
	const sgl::Vector2s left2(left.x + offset.x, left.y + offset.y);

	const sgl::Vertex& pRight = Area::getVertex(g, Direction::Right);
	const sgl::Vector2f right = pRight.getPosition();
	const sgl::Vector2s right2(right.x + offset.x, right.y + offset.y);

	if (ground->Rect.contains(left.x, left.y) || ground->Rect.contains(right.x, right.y)) {
		/// Nur die Rechte oder Linke Ecke ist kollidiert
		if (left.x >= ground->getRight() || right.x <= ground->Rect.x) {
			//std::cout << "Only edge!" << std::endl;
			return Collision::Edge;
		}

		/*
		/// Komplett eingesunken
		if (left.y > ground->Rect.y && right.y > ground->Rect.y) {
			std::cout << "Plugged!" << std::endl;
			return Collision::Plugged;
		}
		*/

		return Collision::Yes;
	} else if (ground->Rect.contains(left2.x, left2.y) || ground->Rect.contains(right2.x, right2.y)) {
		//std::cout << "Next time" << std::endl;
		return Collision::Next;
	}

	return Collision::No;
}