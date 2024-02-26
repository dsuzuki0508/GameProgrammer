#include "Game/StaticObject.h"
#include "GameLib/Framework.h"
#include "Defines.h"
#include <algorithm>

using namespace std;

StaticObject::StaticObject():
mFlags(0),
mDelCounter(),
mBombPow(0)
{
}

void StaticObject::update()
{
	auto f = GameLib::Framework::instance();
	for (auto& e : mDelCounter) {
		e.second -= min(e.second, f.previousFrameInterval());
	}
	if (isSet(Flag::FLAG_HORIZONTAL_BLAST) || isSet(Flag::FLAG_VERTICAL_BLAST)) {
		if (isSet(Flag::FLAG_BOMB))mDelCounter[Flag::FLAG_BOMB] = 0;
	}
	if (!isSet(Flag::FLAG_BRICK)) {
		if (isSet(Flag::FLAG_HORIZONTAL_BLAST) || isSet(Flag::FLAG_VERTICAL_BLAST)) {
			unsetFlag(Flag::FLAG_ITEM_BOMB);
			unsetFlag(Flag::FLAG_ITEM_POWER);
		}
	}
}

void StaticObject::draw(unsigned y, unsigned x, const std::unique_ptr<CellsImage>& cells_image_ptr)const {
	y *= 16;
	x *= 16;
	if (isSet(Flag::FLAG_WALL)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_WALL);
		return;
	}
	if (isSet(Flag::FLAG_BRICK)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_BRICK);
		if (isSet(Flag::FLAG_VERTICAL_BLAST) && isSet(Flag::FLAG_HORIZONTAL_BLAST)) {
			cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_CROSSED_BLAST);
		}
		else {
			if (isSet(Flag::FLAG_VERTICAL_BLAST)) {
				cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_VERTICAL_BLAST);
			}
			if (isSet(Flag::FLAG_HORIZONTAL_BLAST)) {
				cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_HORIZONTAL_BLAST);
			}
		}
		return;
	}
	cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_SPACE);
	if (isSet(Flag::FLAG_ITEM_BOMB)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_ITEM_BOMB);
	}
	if (isSet(Flag::FLAG_ITEM_POWER)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_ITEM_POWER);
	}
	if (isSet(Flag::FLAG_BOMB)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_BOMB);
	}
	if (isSet(Flag::FLAG_VERTICAL_BLAST) && isSet(Flag::FLAG_HORIZONTAL_BLAST)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_CROSSED_BLAST);
	}
	else {
		if (isSet(Flag::FLAG_VERTICAL_BLAST)) {
			cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_VERTICAL_BLAST);
		}
		if (isSet(Flag::FLAG_HORIZONTAL_BLAST)) {
			cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_HORIZONTAL_BLAST);
		}
	}
}
bool StaticObject::isSet(Flag flag)const {
	return (mFlags & static_cast<unsigned>(flag)) > 0;
}
bool StaticObject::isSpace() const
{
	return mFlags == static_cast<unsigned>(Flag::FLAG_SPACE);
}
void StaticObject:: setFlag(Flag flag) {
	mFlags |= static_cast<unsigned>(flag);
	if (flag == Flag::FLAG_BOMB) {
		mDelCounter[Flag::FLAG_BOMB] = EXPLODE_TIME;
	}
	if (flag == Flag::FLAG_HORIZONTAL_BLAST || flag == Flag::FLAG_VERTICAL_BLAST) {
		mDelCounter[flag] = EXPLOSING_TIME;
	}
}
void StaticObject::putBomb(unsigned bomb_pow, unsigned bomb_owner)
{
	if (isSet(Flag::FLAG_BOMB))return;
	if (isSet(Flag::FLAG_HORIZONTAL_BLAST))return;
	if (isSet(Flag::FLAG_VERTICAL_BLAST))return;
	setFlag(Flag::FLAG_BOMB);
	mBombPow = bomb_pow;
	mBombOwner = bomb_owner;
}
void StaticObject::unsetFlag(Flag flag) {
	mFlags &= ~static_cast<unsigned>(flag);
}
void StaticObject::resetFlag(unsigned flags) {
	mFlags = flags;
}
void StaticObject::resetFlag(Flag flag) {
	mFlags = static_cast<unsigned>(flag);
}

int StaticObject::getDelCounter(Flag flag) const
{
	return mDelCounter.at(flag);
}

int StaticObject::getBombPow() const
{
	if (isSet(Flag::FLAG_BOMB)) {
		return mBombPow;
	}
	return 0;
}

int StaticObject::getBombOwner() const
{
	return mBombOwner;
}
