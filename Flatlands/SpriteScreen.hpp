#ifndef SPRITE_SCREEN
#define SPRITE_SCREEN

#include <SGL\Graphic\Sprite.hpp>
#include <SGL\Graphic\Image.hpp>
#include "Screen.hpp"

class SpriteScreen : public Screen {
protected:
	sgl::Image _img;
	sgl::Sprite _sprite;

public:
	explicit SpriteScreen(const sgl::Window& wnd, const std::string& filename);

	virtual void render(bool) const override {
		_wnd.draw(_sprite);
	}
};

#endif