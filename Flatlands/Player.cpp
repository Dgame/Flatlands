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
	const sgl::Vertex& pRight = Area::getVertex(g, Direction::Right);

	if (ground->Rect.contains(pLeft.x, pLeft.y) || ground->Rect.contains(pRight.x, pRight.y)) {
		if (pLeft.x >= ground->getRight() || pRight.x <= ground->Rect.x)
			return Collision::Edge;

		return Collision::Yes;
	} else {
		switch (g) {
			case Gravity::Down:
				for (uint16 i = 8; i < offset.y; i += 8) {
					if (ground->Rect.contains(pLeft.x, pLeft.y + i) || ground->Rect.contains(pRight.x, pRight.y + i)) {
						return Collision::Next;
					}
				}
				break;
			case Gravity::Up:
				for (int16 i = -8; i > offset.y; i -= 8) {
					if (ground->Rect.contains(pLeft.x, pLeft.y + i) || ground->Rect.contains(pRight.x, pRight.y + i)) {
						return Collision::Next;
					}
				}
				break;
		}
	}

	return Collision::No;
}