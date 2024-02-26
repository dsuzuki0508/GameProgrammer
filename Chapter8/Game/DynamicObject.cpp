#include "DynamicObject.h"
#include "GameLib/Framework.h"
#include "Defines.h"
#include <utility>
#include <algorithm>
#include <sstream>

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


DynamicObject::DynamicObject(unsigned y, unsigned x, Type type) :
	mType(type),
	mSize(7<<10),
	mY((y<<14)+(8<<10)),
	mX((x<<14)+ (8 << 10)),
	mD(make_pair(0, 0)),
	mIsAlive(true),
	mMaxBomb(10),
	mBombPow(10),
	mBombs(0)
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
	if (!mIsAlive)return;
	pair<int, int> pos = getPixelPos();
	switch (mType)
	{
	case DynamicObject::Type::TYPE_1P:
		cells_image_ptr->drawImage(pos.first-8, pos.second-8, CellsImage::Id::IMG_PLAYER1);
		break;
	case DynamicObject::Type::TYPE_2P:
		cells_image_ptr->drawImage(pos.first - 8, pos.second - 8, CellsImage::Id::IMG_PLAYER2);
		break;
	case DynamicObject::Type::TYPE_ENEMY:
		cells_image_ptr->drawImage(pos.first - 8, pos.second - 8, CellsImage::Id::IMG_ENEMY);
		break;
	case DynamicObject::Type::TYPE_UNKNOWN:
		break;
	default:
		break;
	}
}


void DynamicObject::update(std::vector<std::vector<StaticObject>>& static_objects)
{
	if (!mIsAlive)return;
	GameLib::Framework f = GameLib::Framework::instance();
	vector<pair<int, int> > tmp = { {-1,0},{1,0},{0,-1},{0,1} };
	if (mType == Type::TYPE_1P) {
		mD = { 0,0 };
		if (f.isKeyOn('w')) mD.first = -1;
		else if (f.isKeyOn('z')) mD.first = 1;
		if (f.isKeyOn('a')) mD.second = -1;
		else if (f.isKeyOn('s')) mD.second = 1;
	}
	else if (mType == Type::TYPE_2P) {
		mD = { 0,0 };
		if (f.isKeyOn('i')) mD.first = -1;
		else if (f.isKeyOn('m')) mD.first = 1;
		if (f.isKeyOn('j')) mD.second = -1;
		else if (f.isKeyOn('k')) mD.second = 1;
	}
	else if (mType == Type::TYPE_ENEMY) {
		if (mD == make_pair(0, 0)) {
			mD = tmp[f.getRandom(4)];
		}
	}
	int moved = move(static_objects, mD);
	if (moved == 0 && mType == Type::TYPE_ENEMY) {
		for (auto const e : tmp)if (mD == e)tmp.erase(find(tmp.begin(), tmp.end(), e));
		mD = tmp[f.getRandom(3)];
	}
	if (mType == Type::TYPE_1P || mType == Type::TYPE_2P) {
		auto internal_pos = getInternalPos();
		auto cell_pos = getCellPos();
		if (mLastBombs[0].first != -1 && mLastBombs[0].second != -1) {
			if (!collision(internal_pos, mLastBombs[0].first, mLastBombs[0].second)) {
				mLastBombs[0] = make_pair(-1, -1);
			}
		}
		if (mLastBombs[1].first != -1 && mLastBombs[1].second != -1) {
			if (!collision(internal_pos, mLastBombs[1].first, mLastBombs[1].second)) {
				mLastBombs[1] = make_pair(-1, -1);
			}
		}
		if (mLastBombs[2].first != -1 && mLastBombs[2].second != -1) {
			if (!collision(internal_pos, mLastBombs[2].first, mLastBombs[2].second)) {
				mLastBombs[2] = make_pair(-1, -1);
			}
		}
	
	}

	for (int y = max(0, getCellPos().first - 1); y <= min(HEIGHT, getCellPos().first + 1); y++) {
		for (int x = max(0, getCellPos().second - 1); x <= min(WIDTH, getCellPos().second + 1); x++) {
			if (collision(getInternalPos(), y, x)) {
				if (static_objects[y][x].isSet(StaticObject::Flag::FLAG_VERTICAL_BLAST) ||
					static_objects[y][x].isSet(StaticObject::Flag::FLAG_HORIZONTAL_BLAST)) {
					die();
				}
				if (static_objects[y][x].isSet(StaticObject::Flag::FLAG_ITEM_BOMB)) {
					mMaxBomb++;
					static_objects[y][x].unsetFlag(StaticObject::Flag::FLAG_ITEM_BOMB);
				}
				if (static_objects[y][x].isSet(StaticObject::Flag::FLAG_ITEM_POWER)) {
					mBombPow++;
					static_objects[y][x].unsetFlag(StaticObject::Flag::FLAG_ITEM_POWER);
				}
			}
		}
	}

}

bool DynamicObject::isAlive()const
{
	return mIsAlive;
}

void DynamicObject::die()
{
	//if (mType == Type::TYPE_1P)return;
	mIsAlive = false;
}
int DynamicObject::move(std::vector<std::vector<StaticObject>>& static_objects, pair<int,int> d)
{
	int ret = 0;
	GameLib::Framework f = GameLib::Framework::instance();
	int total_movement = (PIXEL_PAR_SEC << 10) * f.previousFrameInterval() / 1000;
	total_movement = min(total_movement, 24 << 10);
	int moved_value =  calcMovementValue(static_objects, d, total_movement);
	ret += moved_value;

	mY += d.first * moved_value;
	mX += d.second * moved_value;
	int remain_movement = total_movement - moved_value;
	int y_movement = calcMovementValue(static_objects, { d.first, 0 }, remain_movement);
	int x_movement = calcMovementValue(static_objects, { 0,d.second }, remain_movement);
	if (y_movement > x_movement) {
		mY += d.first * y_movement;
		if(d.first!=0)ret += y_movement;
	}
	else {
		mX += d.second * x_movement;
		if(d.second!=0)ret += x_movement;
	}
	return ret;
}

int DynamicObject::calcMovementValue(std::vector<std::vector<StaticObject>>& static_objects, std::pair<int, int> d, int max_movement)
{
	int left = 0;
	int right = max_movement;

	while (left != right) {
		int mid = (left + right + 1) / 2;
		bool ok = true;
		pair<int, int> tmpd = d * mid + getInternalPos();
		for (int y = max(0, getCellPos().first - 1); y <= min(HEIGHT, getCellPos().first + 1); y++) {
			for (int x = max(0, getCellPos().second - 1); x <= min(WIDTH, getCellPos().second + 1); x++) {
				if (!static_objects[y][x].isSet(StaticObject::Flag::FLAG_WALL) &&
					!static_objects[y][x].isSet(StaticObject::Flag::FLAG_BRICK) &&
					!static_objects[y][x].isSet(StaticObject::Flag::FLAG_BOMB))continue;
				pair<int, int> pos = { y,x };
				if (mType == Type::TYPE_1P && d != pair<int, int>(0, 0)) {
					//GameLib::Framework::instance().drawDebugString(4, 4, "ERROR!");
				}
				if (pos == mLastBombs[0] || pos == mLastBombs[1] || pos == mLastBombs[2]) {
					continue;
				}

				if (collision(tmpd, y, x)) {
					ok = false;
					break;
				}
			}
			if (!ok)break;
		}
		if (ok) {
			left = mid;
		}
		else {
			right = mid - 1;
		}
	}
	return left;
}

int DynamicObject::getTop()
{
	return mY - (7 << 10);
}

int DynamicObject::getBottom()
{
	return mY + (7 << 10);
}

int DynamicObject::getLeft()
{
	return mX - (7 << 10);
}

int DynamicObject::getRight()
{
	return mX + (7 << 10);
}

std::pair<int, int> DynamicObject::getCellPos() const
{
	pair<int, int> res = getPixelPos();
	res = res / 16;
	return res;
}

bool DynamicObject::setBomb()
{
	if (mBombs < mMaxBomb) {
		mBombs++;
		mLastBombs[0] = mLastBombs[1];
		mLastBombs[1] = mLastBombs[2];
		mLastBombs[2] = getCellPos();
		return true;
	}
	return false;
}

void DynamicObject::reduceBomb()
{
	mBombs--;
}

unsigned DynamicObject::getBombPow() const
{
	return mBombPow;
}

unsigned DynamicObject::getSize() const
{
	return mSize;
}

bool DynamicObject::collision(std::pair<int, int> internal_pos, int internal_size)
{
	return !(mY + mSize < internal_pos.first - internal_size || internal_pos.first + internal_size < mY - mSize || mX + mSize < internal_pos.second - internal_size || internal_pos.second + internal_size < mX - mSize);
}

std::pair<int, int> DynamicObject::getPixelPos() const
{
	pair<int, int> res = getInternalPos();
	res.first += 512;
	res.second += 512;
	res = res / 1024;
	return res;
}

std::pair<int, int> DynamicObject::getInternalPos() const
{
	return std::pair<int, int>( mY, mX);
}


bool DynamicObject::collision(pair<int,int> internal_pos, int internal_y, int internal_x, int internal_size) {
	return !(internal_pos.first + mSize < internal_y - internal_size || internal_y + internal_size < internal_pos.first - mSize || internal_pos.second + mSize < internal_x - internal_size || internal_x + internal_size < internal_pos.second - mSize);
}

bool DynamicObject::collision(pair<int,int> internal_pos, int cell_y, int cell_x) {
	return collision(internal_pos, ((cell_y << 4) + 8) << 10, ((cell_x << 4) + 8) << 10, 8 << 10);
}

