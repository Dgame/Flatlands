#ifndef GROUND_HPP
#define GROUND_HPP

#include <SGL\Math\Rect.hpp>
#include "Area.hpp"

#define MinGroundHeight 64

class Ground final : public Area {
public:
	const sgl::ShortRect Rect;

	explicit Ground(const sgl::ShortRect& rect);

	uint16 getRight() const {
		return this->Rect.width + this->Rect.x;
	}
};

#endif