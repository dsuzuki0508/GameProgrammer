#ifndef GAME_STATICOBJECT_H
#define GAME_STATICOBJECT_H
#include <memory>
#include "Image.h"
class StaticObject {
public:
	enum class Flag {
		FLAG_SPACE = 0,
		FLAG_WALL = (1<<0),
		FLAG_BRICK = (1<<1),
		FLAG_ITEM_BOMB = (1<<2),
		FLAG_ITEM_POWER = (1<<3),
		FLAG_BOMB = (1<<4),
	};
	StaticObject();

	void draw(unsigned y, unsigned x, const std::unique_ptr<CellsImage>& cells_image_ptr)const;
	bool isSet(Flag flag)const;
	bool isSpace()const;
	void setFlag(Flag flag);
	void unsetFlag(Flag flag);
	void resetFlag(unsigned flags);
	void resetFlag(Flag flag);

private:
	unsigned mFlags;
};
#endif // GAME_STATICOBJECT_H