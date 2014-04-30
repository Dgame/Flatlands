#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <memory>
#include <SGL\Math\Rect.hpp>
#include "Ground.hpp"

struct Level {
	sgl::Vector2s startPosition;
	std::vector<sgl::ShortRect> rects;
};

class LevelManager final {
private:
	std::vector<Level> _levels;
	int16 _lvlNr = -1;

public:
	explicit LevelManager();

	uint16 getLevelNumber() const {
		return _lvlNr;
	}

	const Level& getCurrentLevel() const {
		return _levels[_lvlNr];
	}

	bool loadLevel(uint16 lvl, std::vector<std::unique_ptr<Ground>>& grounds);

	bool loadNextLevel(std::vector<std::unique_ptr<Ground>>& grounds) {
		return this->loadLevel(_lvlNr + 1, grounds);
	}
};

#endif