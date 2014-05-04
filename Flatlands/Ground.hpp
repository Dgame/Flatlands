#ifndef GROUND_HPP
#define GROUND_HPP

#include <SGL\Math\Rect.hpp>
#include "Area.hpp"

#define MinGroundHeight 64

class Ground final : public Area {
protected:
	virtual void draw(const sgl::Window& wnd) const override;

public:
	const sgl::ShortRect Rect;
	const sgl::ShortRect* targetRect = nullptr;
	std::unique_ptr<Area> target;

	explicit Ground(const sgl::ShortRect& rect);

	bool isTarget() const {
		return this->target.get() != nullptr;
	}

	uint16 getRight() const {
		return this->Rect.width + this->Rect.x;
	}
};

#endif