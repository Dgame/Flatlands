#include "Area.hpp"

Area::Area(sgl::Shape::Type type) : sgl::Shape(type) {
	sgl::Shape::smooth.set(sgl::Smooth::Target::Line, sgl::Smooth::Mode::Nicest);
}