#include "Game/StaticObject.h"



StaticObject::StaticObject() {
}

void StaticObject::draw(unsigned y, unsigned x, const std::unique_ptr<CellsImage>& cells_image_ptr)const {
	y *= 16;
	x *= 16;
	if (!mFlags) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_SPACE);
		return;
	}
	if (isSet(Flag::FLAG_WALL)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_WALL);
		return;
	}
	if (isSet(Flag::FLAG_BRICK)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_BRICK);
		return;
	}
	if (isSet(Flag::FLAG_ITEM_BOMB)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_ITEM_BOMB);
	}
	if (isSet(Flag::FLAG_ITEM_POWER)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_ITEM_POWER);
	}
	if (isSet(Flag::FLAG_BOMB)) {
		cells_image_ptr->drawImage(y, x, CellsImage::Id::IMG_BOMB);
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
