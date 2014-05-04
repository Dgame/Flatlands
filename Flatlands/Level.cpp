#include "Level.hpp"

LevelManager::LevelManager() {
	Level lvl = { /// Level #1
		sgl::Vector2s(400, 0),
		sgl::ShortRect(200, 432, 96, MinGroundHeight),
		{
			{sgl::ShortRect(320, 128, 200, MinGroundHeight), false},
			{sgl::ShortRect(96, 288, 304, MinGroundHeight), false},
			{sgl::ShortRect(4, 432, 396, MinGroundHeight), true}
		}
	};
	_levels.emplace_back(lvl);
	lvl = { /// Level #2
		sgl::Vector2s(24, 0),
		sgl::ShortRect(300, 352, 96, MinGroundHeight),
		{
			{sgl::ShortRect(4, 128, 128, MinGroundHeight), false},
			{sgl::ShortRect(128, 256, 248, MinGroundHeight), false},
			{sgl::ShortRect(256, 352, 256, MinGroundHeight), true}
		}
	};
	_levels.emplace_back(lvl);
}

bool LevelManager::loadLevel(uint16 lvl, std::vector<std::unique_ptr<Ground>>& grounds) {
	if (lvl >= _levels.size())
		return false;

	_lvlNr = lvl;

	grounds.reserve(_levels[lvl].grounds.size());

	uint16 i = 0;
	for (const LevelGround& lg : _levels[lvl].grounds) {
		Ground* ground = new Ground(lg.rect);
		if (lg.isTarget) {
			Area* area = new Area(sgl::Shape::Type::Quad);
			area->addVertices(_levels[lvl].target);
			area->fill = true;
			area->setColor(sgl::Color::Red);

			ground->target.reset(area);
			ground->targetRect = &_levels[lvl].target;
		}

		if (i >= grounds.size())
			grounds.push_back(std::unique_ptr<Ground>(ground));
		else
			grounds[i].reset(ground);

		i++;
	}

	return true;
}