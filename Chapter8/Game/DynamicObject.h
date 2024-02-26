#ifndef GAME_DYNAMICOBJECT_H
#define GAME_DYNAMICOBJECT_H
#include <memory>
#include <utility>
#include "Image.h"
#include "Game/StaticObject.h"
#include <deque>
class DynamicObject
{
public:
	enum class Type {
		TYPE_1P,
		TYPE_2P,
		TYPE_ENEMY,
		TYPE_UNKNOWN,
	};
	DynamicObject(unsigned y, unsigned x, Type type);
//	DynamicObject(const DynamicObject& o);
	void draw( const std::unique_ptr<CellsImage>& cells_image_ptr) const;
	void update(std::vector<std::vector<StaticObject>>& static_objects);
	bool isAlive()const;
	void die();
	int move(std::vector<std::vector<StaticObject>>& static_objects, std::pair<int,int> d);
	std::pair<int, int> getCellPos()const;
	std::pair<int, int> getInternalPos()const;
	bool setBomb();
	void reduceBomb();
	unsigned getBombPow()const;
	unsigned getSize()const;
	bool collision(std::pair<int, int> internal_pos, int internal_size);
private:
	int calcMovementValue(std::vector<std::vector<StaticObject>>& static_objects, std::pair<int, int> d, int moving_time);
	int getTop();
	int getBottom();
	int getLeft();
	int getRight();
	std::pair<int, int> getPixelPos()const;
	bool collision(std::pair<int, int> internal_pos, int internal_y, int internal_x, int internal_size);
	bool collision(std::pair<int, int> internal_pos, int cell_y, int cell_x);

	Type mType;
	unsigned mSize;
	unsigned mY;
	unsigned mX;
	std::pair<int, int> mD;
	bool mIsAlive;
	unsigned mMaxBomb;
	unsigned mBombPow;
	unsigned mBombs;
	std::pair<int, int> mLastBombs[3] = { {-1,-1},{-1,-1},{-1,-1} };
};

#endif // GAME_DYNAMICOBJECT_H
