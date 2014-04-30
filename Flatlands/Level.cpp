#include "Level.hpp"

LevelManager::LevelManager() {
	Level lvl = { /// Level #1
		sgl::Vector2s(400, 0),
		{
			sgl::ShortRect(320, 96, 200, MinGroundHeight),
			sgl::ShortRect(96, 256, 304, MinGroundHeight),
			sgl::ShortRect(4, 400, 448, MinGroundHeight),
		}
	};
	_levels.emplace_back(lvl);
	lvl = { /// Level #2
		sgl::Vector2s(24, 0),
		{
			sgl::ShortRect(4, 128, 128, MinGroundHeight),
			sgl::ShortRect(128, 256, 248, MinGroundHeight),
			sgl::ShortRect(256, 352, 256, MinGroundHeight),
		}
	};
	_levels.emplace_back(lvl);
}

bool LevelManager::loadLevel(uint16 lvl, std::vector<std::unique_ptr<Ground>>& grounds) {
	if (lvl >= _levels.size())
		return false;

	_lvlNr = lvl;

	grounds.reserve(_levels[lvl].rects.size());

	uint16 i = 0;
	for (sgl::ShortRect& rect : _levels[lvl].rects) {
		Ground* ground = new Ground(rect);

		if (i >= grounds.size())
			grounds.push_back(std::unique_ptr<Ground>(ground));
		else
			grounds[i].reset(ground);

		i++;
	}

	return true;
}