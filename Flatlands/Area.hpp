#ifndef AREA_HPP
#define AREA_HPP

#include <SGL\Core\Types.hpp>
#include <SGL\Math.hpp>
#include <SGL\Graphic\Shape.hpp>
#include "Force.hpp"

const uint16 RectIndices[2][2] = {
	{3, 2},
	{0, 1}
};

enum Direction : short {
	Left = 0,
	Right = 1
};

class Area : public sgl::Shape {
public:
	explicit Area(sgl::Shape::Type);

	const sgl::Vertex& getVertex(Gravity g, Direction dir) const {
		return sgl::Shape::vertices[RectIndices[g][dir]];
	}
};

#endif