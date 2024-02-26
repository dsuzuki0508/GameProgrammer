#include "DynamicObject.h"
#include "GameLib/Framework.h"
#include "Defines.h"
#include <utility>
#include <algorithm>

using namespace std;


template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U>& l, const std::pair<T, U>& r) {
	return { l.first + r.first,l.second + r.second };
}
template <typename T, typename U>
std::pair<T, U> operator-(const std::pair<T, U>& l, const std::pair<T, U>& r) {
	return { l.first - r.first,l.second - r.second };
}
template <typename T, typename U>
std::pair<T, U> operator*(const std::pair<T, U>& l, const unsigned r) {
	return { l.first * r,l.second * r };
}
template <typename T, typename U>
std::pair<T, U> operator/(const std::pair<T, U>& l, const unsigned r) {
	return { l.first / r,l.second / r };
}


DynamicObject::DynamicObject(unsigned y, unsigned x, Type type):
	mType(type),
	mY((y<<14)+512),
	mX((x<<14)+512)
{

}
/*
DynamicObject::DynamicObject(const DynamicObject& o):
	mType(o.mType),
	mY(o.mY),
	mX(o.mX)
{
}
*/
void DynamicObject::draw(const std::unique_ptr<CellsImage>& cells_image_ptr) const
{
	switch (mType)
	{
	case DynamicObject::Type::TYPE_1P:
		cells_image_ptr->drawImage(mY >> 10, mX >> 10, CellsImage::Id::IMG_PLAYER1);
		break;
	case DynamicObject::Type::TYPE_2P:
		cells_image_ptr->drawImage(mY >> 10, mX >> 10, CellsImage::Id::IMG_PLAYER2);
		break;
	case DynamicObject::Type::TYPE_ENEMY:
		cells_image_ptr->drawImage(mY >> 10, mX >> 10, CellsImage::Id::IMG_ENEMY);
		break;
	case DynamicObject::Type::TYPE_UNKNOWN:
		break;
	default:
		break;
	}
}


void DynamicObject::update()
{
	GameLib::Framework f = GameLib::Framework::instance();
	pair<int, int> d;
	if (mType == Type::TYPE_1P) {
		if (f.isKeyOn('w')) d.first = -1;
		else if (f.isKeyOn('z')) d.first = 1;
		else if (f.isKeyOn('a')) d.second = -1;
		else if (f.isKeyOn('s')) d.second = 1;
	}
	else if (mType == Type::TYPE_2P) {
		if (f.isKeyOn('i')) d.first = -1;
		else if (f.isKeyOn('m')) d.first = 1;
		else if (f.isKeyOn('j')) d.second = -1;
		else if (f.isKeyOn('k')) d.second = 1;
	}
	else if (mType == Type::TYPE_ENEMY) {
		vector<pair<int, int> > tmp = { {-1,0},{1,0},{0,-1},{0,1} };
		d = tmp[f.getRandom(4)];
	}
	d = d* ((PIXEL_PAR_SEC << 10) * f.previousFrameInterval() / 1000);
	mY += d.first;
	mX += d.second;
	mY = min(max(static_cast<int>(mY), 0), (HEIGHT - 1) << 14);
	mX = min(max(static_cast<int>(mX), 0), (WIDTH - 1) << 14);
}
