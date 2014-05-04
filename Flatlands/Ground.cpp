#include <SGL\Window\Window.hpp>
#include "Ground.hpp"

Ground::Ground(const sgl::ShortRect& rect, bool isTarget) : Area(sgl::Shape::Type::Quad), Rect(rect), _isTarget(isTarget) {
	sgl::Shape::addVertices(rect);

	if (!isTarget)
		sgl::Shape::setColor(sgl::Color("#033b22"));
	else {
		sgl::Shape::setColor(sgl::Color::Red);
		//sgl::Shape::fill = true;
	}
}