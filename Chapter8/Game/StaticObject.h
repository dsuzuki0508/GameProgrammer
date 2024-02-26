#ifndef GAME_STATICOBJECT_H
#define GAME_STATICOBJECT_H
#include <memory>
#include <map>
#include "Image.h"
class StaticObject {
public:
	enum class Flag {
		FLAG_SPACE = 0,
		FLAG_WALL = (1 << 0),
		FLAG_BRICK = (1 << 1),
		FLAG_ITEM_BOMB = (1 << 2),
		FLAG_ITEM_POWER = (1 << 3),
		FLAG_BOMB = (1 << 4),
		FLAG_HORIZONTAL_BLAST = (1 << 5),
		FLAG_VERTICAL_BLAST = (1 << 6),
	};
	StaticObject();
	void update();
	void draw(unsigned y, unsigned x, const std::unique_ptr<CellsImage>& cells_image_ptr)const;
	bool isSet(Flag flag)const;
	bool isSpace()const;
	void setFlag(Flag flag);
	void putBomb(unsigned bomb_pow, unsigned bomb_owner);
	void unsetFlag(Flag flag);
	void resetFlag(unsigned flags);
	void resetFlag(Flag flag);
	int getDelCounter(Flag flag)const;
	int getBombPow()const;
	int getBombOwner()const;

private:
	unsigned mFlags;
	std::map<Flag, int> mDelCounter;
	unsigned mBombPow;
	unsigned mBombOwner;

};
#endif // GAME_STATICOBJECT_H