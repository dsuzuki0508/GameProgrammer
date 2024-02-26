#include "State.h"
#include "Pad.h"

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
	mVSMode = (mStageId == 0);

	for (auto& e : mStaticObjects) {
		e[0].resetFlag(StaticObject::Flag::FLAG_WALL);
		e[WIDTH - 1].resetFlag(StaticObject::Flag::FLAG_WALL);
	}
	for (auto& e : mStaticObjects[0])e.resetFlag(StaticObject::Flag::FLAG_WALL);
	for (auto& e : mStaticObjects[HEIGHT-1])e.resetFlag(StaticObject::Flag::FLAG_WALL);
	unsigned space = (HEIGHT - 2) * (WIDTH - 2);
	space -= ((HEIGHT - 2) / 2) * ((WIDTH - 2) / 2);
	space -= mVSMode ? 6: 3;
	unsigned brick = space * data.mBrickRate / 100;
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {
			if (i + j <= 3) {
				mStaticObjects[i][j].resetFlag(StaticObject::Flag::FLAG_SPACE);
				continue;
			}
			if (mVSMode && HEIGHT + WIDTH - 5 <= i + j) {
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
	space -= mVSMode ? 6 : 3;
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
	if (mVSMode) {
		mDynamicObjects.push_back({ HEIGHT-2,WIDTH-2,DynamicObject::Type::TYPE_2P });
	}
	space = (HEIGHT - 2) * (WIDTH - 2);
	space -= ((HEIGHT - 2) / 2) * ((WIDTH - 2) / 2);
	space -= mVSMode ? 6 : 3;
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

void State::update() {
	auto f = GameLib::Framework::instance();
	for (auto& e : mDynamicObjects) {
		e.update(mStaticObjects);
	}
	for (int i = mVSMode ? 2 : 1; i < mDynamicObjects.size(); i++) {
		if (!mDynamicObjects[i].isAlive())continue;
		if (mDynamicObjects[0].collision(mDynamicObjects[i].getInternalPos(), mDynamicObjects[i].getSize())) {
			mDynamicObjects[0].die();
		}
	}
	if (mVSMode) {
		for (int i = 2; i < mDynamicObjects.size(); i++) {
			if (!mDynamicObjects[i].isAlive())continue;
			if (mDynamicObjects[1].collision(mDynamicObjects[i].getInternalPos(), mDynamicObjects[i].getSize())) {
				mDynamicObjects[1].die();
			}
		}
	}
	for (int i = 0; i < mStaticObjects.size(); i++) {
		for (int j = 0; j < mStaticObjects[i].size(); j++) {
			mStaticObjects[i][j].update();
		}
	}
	for (int i = 0; i < mStaticObjects.size(); i++) {
		for (int j = 0; j < mStaticObjects[i].size(); j++) {
			if (mStaticObjects[i][j].isSet(StaticObject::Flag::FLAG_BOMB) && 
				mStaticObjects[i][j].getDelCounter(StaticObject::Flag::FLAG_BOMB) == 0) {
				int bomb_pow = mStaticObjects[i][j].getBombPow();
				mDynamicObjects[mStaticObjects[i][j].getBombOwner()].reduceBomb();
				mStaticObjects[i][j].unsetFlag(StaticObject::Flag::FLAG_BOMB);
				mStaticObjects[i][j].setFlag(StaticObject::Flag::FLAG_HORIZONTAL_BLAST);
				mStaticObjects[i][j].setFlag(StaticObject::Flag::FLAG_VERTICAL_BLAST);
				for (int y = i - 1; y > max(0, i-1-bomb_pow); y--) {
					if (mStaticObjects[y][j].isSet(StaticObject::Flag::FLAG_WALL))break;
					mStaticObjects[y][j].setFlag(StaticObject::Flag::FLAG_VERTICAL_BLAST);
					if (mStaticObjects[y][j].isSet(StaticObject::Flag::FLAG_BRICK))break;
					if (mStaticObjects[y][j].isSet(StaticObject::Flag::FLAG_BOMB))break;
				}
				for (int y = i + 1; y < min(HEIGHT,i+1+bomb_pow); y++) {
					if (mStaticObjects[y][j].isSet(StaticObject::Flag::FLAG_WALL))break;
					mStaticObjects[y][j].setFlag(StaticObject::Flag::FLAG_VERTICAL_BLAST);
					if (mStaticObjects[y][j].isSet(StaticObject::Flag::FLAG_BRICK))break;
					if (mStaticObjects[y][j].isSet(StaticObject::Flag::FLAG_BOMB))break;
				}
				for (int x = j - 1; x > max(0,j-1-bomb_pow); x--) {
					if (mStaticObjects[i][x].isSet(StaticObject::Flag::FLAG_WALL))break;
					mStaticObjects[i][x].setFlag(StaticObject::Flag::FLAG_HORIZONTAL_BLAST);
					if (mStaticObjects[i][x].isSet(StaticObject::Flag::FLAG_BRICK))break;
					if (mStaticObjects[i][x].isSet(StaticObject::Flag::FLAG_BOMB))break;
				}
				for (int x = j + 1; x < min(WIDTH,j+1+bomb_pow); x++) {
					if (mStaticObjects[i][x].isSet(StaticObject::Flag::FLAG_WALL))break;
					mStaticObjects[i][x].setFlag(StaticObject::Flag::FLAG_HORIZONTAL_BLAST);
					if (mStaticObjects[i][x].isSet(StaticObject::Flag::FLAG_BRICK))break;
					if (mStaticObjects[i][x].isSet(StaticObject::Flag::FLAG_BOMB))break;
				}
			}
			if (mStaticObjects[i][j].isSet(StaticObject::Flag::FLAG_HORIZONTAL_BLAST) &&
				mStaticObjects[i][j].getDelCounter(StaticObject::Flag::FLAG_HORIZONTAL_BLAST) == 0) {
				mStaticObjects[i][j].unsetFlag(StaticObject::Flag::FLAG_HORIZONTAL_BLAST);
				mStaticObjects[i][j].unsetFlag(StaticObject::Flag::FLAG_BRICK);
			}
			if (mStaticObjects[i][j].isSet(StaticObject::Flag::FLAG_VERTICAL_BLAST) &&
				mStaticObjects[i][j].getDelCounter(StaticObject::Flag::FLAG_VERTICAL_BLAST) == 0) {
				mStaticObjects[i][j].unsetFlag(StaticObject::Flag::FLAG_VERTICAL_BLAST);
				mStaticObjects[i][j].unsetFlag(StaticObject::Flag::FLAG_BRICK);
			}
		}
	}
	/*
	for (int i = 0; i < mDynamicObjects.size(); i++)
	{
		auto pos = mDynamicObjects[i].getCellPos();
		if (mStaticObjects[pos.first][pos.second].isSet(StaticObject::Flag::FLAG_HORIZONTAL_BLAST) ||
			mStaticObjects[pos.first][pos.second].isSet(StaticObject::Flag::FLAG_VERTICAL_BLAST)) {
			mDynamicObjects[i].die();
		}
	}
	*/
	if (Pad::isOn(Pad::Button::A) && mDynamicObjects[0].isAlive()) {
		
		auto pos = mDynamicObjects[0].getCellPos();
		if (!mStaticObjects[pos.first][pos.second].isSet(StaticObject::Flag::FLAG_BOMB) &&
			!mStaticObjects[pos.first][pos.second].isSet(StaticObject::Flag::FLAG_HORIZONTAL_BLAST) &&
			!mStaticObjects[pos.first][pos.second].isSet(StaticObject::Flag::FLAG_VERTICAL_BLAST)) {
			if (mDynamicObjects[0].setBomb()) {
				unsigned bomb_pow = mDynamicObjects[0].getBombPow();
				mStaticObjects[pos.first][pos.second].putBomb(bomb_pow, 0);
			}
		}
	}
	if (mVSMode && Pad::isOn(Pad::Button::A, 1) && mDynamicObjects[1].isAlive()) {
		auto pos = mDynamicObjects[1].getCellPos();
		if (!mStaticObjects[pos.first][pos.second].isSet(StaticObject::Flag::FLAG_BOMB) &&
			!mStaticObjects[pos.first][pos.second].isSet(StaticObject::Flag::FLAG_HORIZONTAL_BLAST) &&
			!mStaticObjects[pos.first][pos.second].isSet(StaticObject::Flag::FLAG_VERTICAL_BLAST)) {
			if (mDynamicObjects[1].setBomb()) {
				unsigned bomb_pow = mDynamicObjects[1].getBombPow();
				mStaticObjects[pos.first][pos.second].putBomb(bomb_pow, 1);
			}
		}
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
	if (mVSMode)return false;
	int alive = false;
	for (int i = 1; i < mDynamicObjects.size(); i++)alive = (alive || mDynamicObjects[i].isAlive());
	return !alive;
}
bool State::hasFailed() const
{
	if (mVSMode)return false;
	return !mDynamicObjects[0].isAlive();
}
bool State::hasMatchOver() const
{
	if (!mVSMode)return false;
	return !mDynamicObjects[0].isAlive() || !mDynamicObjects[1].isAlive();
}
bool State::isAlive1P()const {
	// return false;
	return mWinner == 1;
}
bool State::isAlive2P()const {
	//return false;
	return mWinner == 2;
}