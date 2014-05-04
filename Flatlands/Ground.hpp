#ifndef GROUND_HPP
#define GROUND_HPP

#include <SGL\Math\Rect.hpp>
#include "Area.hpp"

#define MinGroundHeight 16

class Ground final : public Area {
private:
	bool _isTarget;

public:
	const sgl::ShortRect Rect;

	explicit Ground(const sgl::ShortRect& rect, bool isTarget);

	bool isTarget() const {
		return _isTarget;
	}

	uint16 getRight() const {
		return this->Rect.width + this->Rect.x;
	}
};

#endif