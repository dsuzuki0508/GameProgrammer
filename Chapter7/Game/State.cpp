#include "State.h"

#include <assert.h>

#include "GameLib/Framework.h"
#include "Image.h"
#include "Defines.h"
#include "Game/Move.h"
#include "Game/StaticObject.h"
#include "Game/DynamicObject.h"
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

State::State(unsigned stage_id) :
	mCellsImagePtr(new CellsImage("data/image/cells.dds")),
	mStaticObjects(vector<vector<StaticObject>>(HEIGHT, vector<StaticObject>(WIDTH))),
	mStageId(stage_id),
	mWinner(0)
{
	GameLib::Framework f = GameLib::Framework::instance();
	StageData data = gStageData[mStageId];
	bool vs_mode = mStageId == 0;

	for (auto& e : mStaticObjects) {
		e[0].resetFlag(StaticObject::Flag::FLAG_WALL);
		e[WIDTH - 1].resetFlag(StaticObject::Flag::FLAG_WALL);
	}
	for (auto& e : mStaticObjects[0])e.resetFlag(StaticObject::Flag::FLAG_WALL);
	for (auto& e : mStaticObjects[HEIGHT-1])e.resetFlag(StaticObject::Flag::FLAG_WALL);
	unsigned space = (HEIGHT - 2) * (WIDTH - 2);
	space -= ((HEIGHT - 2) / 2) * ((WIDTH - 2) / 2);
	space -= vs_mode ? 6: 3;
	unsigned brick = space * data.mBrickRate / 100;
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {
			if (i + j <= 3) {
				mStaticObjects[i][j].resetFlag(StaticObject::Flag::FLAG_SPACE);
				continue;
			}
			if (vs_mode && HEIGHT + WIDTH - 5 <= i + j) {
				mStaticObjects[i][j].resetFlag(StaticObject::Flag::FLAG_SPACE);
				continue;
			}
			if (!(i & 1 || j & 1)) {
				mStaticObjects[i][j].resetFlag(StaticObject::Flag::FLAG_WALL);
				continue;
			}
			if (f.getRandom(space) < static_cast<int>(brick)) {
				mStaticObjects[i][j].resetFlag(StaticObject::Flag::FLAG_BRICK);
				brick--;
			}
			else {
				mStaticObjects[i][j].resetFlag(StaticObject::Flag::FLAG_SPACE);
			}
			space--;
		}
	}
	space = (HEIGHT - 2) * (WIDTH - 2);
	space -= ((HEIGHT - 2) / 2) * ((WIDTH - 2) / 2);
	space -= vs_mode ? 6 : 3;
	brick = space * data.mBrickRate / 100;
	unsigned bomb = data.mItemBombNumber;
	unsigned power = data.mItemPowerNumber;
	assert(bomb + power <= brick);
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {
			if (!mStaticObjects[i][j].isSet(StaticObject::Flag::FLAG_BRICK))continue;
			unsigned r = f.getRandom(brick);
			brick--;
			if (r < bomb + power) {
				if (r < bomb) {
					mStaticObjects[i][j].setFlag(StaticObject::Flag::FLAG_ITEM_BOMB);
					bomb--;
				}
				else {
					mStaticObjects[i][j].setFlag(StaticObject::Flag::FLAG_ITEM_POWER);
					power--;
				}
			}
		}
	}

	mDynamicObjects.push_back({ 1,1,DynamicObject::Type::TYPE_1P });
	if (vs_mode) {
		mDynamicObjects.push_back({ HEIGHT-2,WIDTH-2,DynamicObject::Type::TYPE_2P });
	}
	space = (HEIGHT - 2) * (WIDTH - 2);
	space -= ((HEIGHT - 2) / 2) * ((WIDTH - 2) / 2);
	space -= vs_mode ? 6 : 3;
	brick = space * data.mBrickRate / 100;
	space -= brick;
	unsigned enemy = data.mEnemyNumber;
	assert(bomb + power <= brick);
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {
			if (!mStaticObjects[i][j].isSpace())continue;
			unsigned r = f.getRandom(space);
			space--;
			if (r < enemy) {
				mDynamicObjects.push_back({ static_cast<unsigned>(i),static_cast<unsigned>(j), DynamicObject::Type::TYPE_ENEMY });
				enemy--;
			}
		}
	}

}

void State::update(const Move& m) {
	for (auto& e : mDynamicObjects) {
		e.update();
	}
}
void State::draw()const {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			mStaticObjects[i][j].draw(i, j, mCellsImagePtr);
		}
	}
	for (int i = 0; i < static_cast<int>(mDynamicObjects.size()); i++) {
		mDynamicObjects[i].draw(mCellsImagePtr);
	}
	
}
bool State::hasCleared() const {
	return false;
}
bool State::isAlive1P()const {
	// return false;
	return mWinner == 1;
}
bool State::isAlive2P()const {
	//return false;
	return mWinner == 2;
}