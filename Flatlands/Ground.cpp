#include "Ground.hpp"

Ground::Ground(const sgl::ShortRect& rect) : Area(sgl::Shape::Type::Quad), Rect(rect) {
	sgl::Shape::addVertices(rect);
	sgl::Shape::setColor(sgl::Color("#033b22"));
	//sgl::Shape::fill = true;
}