#include "State.h"

#include <assert.h>

#include "GameLib/Framework.h"
#include "Move.h"
#include "Image.h"
using namespace std;


template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U>& l, const std::pair<T, U>& r) {
	return { l.first + r.first,l.second + r.second };
}
template <typename T, typename U>
std::pair<T, U> operator-(const std::pair<T, U>& l, const std::pair<T, U>& r) {
	return { l.first - r.first,l.second - r.second };
}

State::State(const char* stageData, int size) {
	vector<unsigned> tmp;
	int tmpPlayer = 0;
	for (int i = 0; i < size; i++) {
		switch (stageData[i]) {
		case ' ':
			tmp.push_back(OBJ_SPACE);
			break;
		case '#':
			tmp.push_back(OBJ_WALL);
			break;
		case 'o':
			tmp.push_back(OBJ_BLOCK);
			break;
		case '.':
			tmp.push_back(OBJ_GOAL);
			break;
		case 'p':
			mPlayer.first = mMap.size();
			mPlayer.second = tmp.size();
			tmp.push_back(OBJ_SPACE);
			break;
		case 'P':
			mPlayer.first = mMap.size();
			mPlayer.second = tmp.size();
			tmp.push_back(OBJ_GOAL);
			break;
		case 'O':
			tmp.push_back(OBJ_BLOCK | OBJ_GOAL);
			break;
		case '\n':
			if (tmp.size())mMap.push_back(tmp);
			tmp.clear();
		default:
			break;
		}
	}
	if (tmp.size())mMap.push_back(tmp);

	int w = mMap[0].size();
	for (int i = 0; i < mMap.size(); i++) {
		assert(mMap[i].size() == w);
	}
	mHight = mMap.size();
	mWidth = w;

}

void State::update(Move& move) {
	pair<int, int> next = mPlayer + move.d();
	if (next.first < 0 || mHight <= next.first || next.second < 0 || mWidth <= next.second) return;
	if (mMap[next.first][next.second] & OBJ_WALL) return;
	if (mMap[next.first][next.second] & OBJ_BLOCK) {
		auto tmp = next + move.d();
		if (tmp.first < 0 || mHight <= tmp.first || tmp.second < 0 || mWidth <= tmp.second) return;
		if (!(mMap[tmp.first][tmp.second] & (OBJ_SPACE | OBJ_GOAL))) {
			return;
		}
		mMap[tmp.first][tmp.second] &= OBJ_GOAL;
		mMap[tmp.first][tmp.second] |= OBJ_BLOCK;
		mMap[next.first][next.second] &= OBJ_GOAL;
		mMap[next.first][next.second] |= OBJ_SPACE;
	}
	assert(mMap[next.first][next.second] | OBJ_SPACE);
	mPlayer = next;
}
void State::drawCell(int y, int x, unsigned color)const {
	unsigned* vram = GameLib::Framework::instance().videoMemory();
	int windowsWidth = GameLib::Framework::instance().width();
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (pow(i - 7.5, 2) + pow(j - 7.5, 2) <= 64) {
				vram[(y * 16 + i) * windowsWidth + (x * 16 + j)] = color;
			}
		}
	}

}
void State::draw(const unique_ptr<Image>& image_ptr)const {
	for (int i = 0; i < mHight; i++) {
		for (int j = 0; j < mWidth; j++) {
			unsigned c = 0x00000000;
			if (mMap[i][j] & OBJ_GOAL) {
				if (mPlayer == make_pair(i, j)) {
					GameLib::cout << 'P';
					c = 0x0000ffff;
				}
				else if (mMap[i][j] & OBJ_BLOCK) {
					GameLib::cout << 'O';
					c = 0x00ff00ff;
				}
				else {
					GameLib::cout << '.';
					c = 0x000000ff;
				}
			}
			else {
				if (mPlayer == make_pair(i, j)) {
					GameLib::cout << 'p';
					c = 0x0000ff00;
				}
				else {
					switch (mMap[i][j]) {
					case OBJ_SPACE:GameLib::cout << ' '; c = 0x00000000; break;
					case OBJ_WALL:GameLib::cout << '#'; c = 0x00ffffff; break;
					case OBJ_BLOCK:GameLib::cout << 'o'; c = 0x00ff0000; break;
					}
				}
			}
			//			drawCell(i, j, c);
			image_ptr->drawImage(i, j, static_cast<Object>(mMap[i][j]), mPlayer == make_pair(i, j));

		}
		GameLib::cout << GameLib::endl;
	}
}
bool State::isClearedState() const {
	for (int i = 0; i < mHight; i++) {
		for (int j = 0; j < mWidth; j++) {
			if ((mMap[i][j] & OBJ_GOAL) && !(mMap[i][j] & OBJ_BLOCK)) {
				return false;
			}
		}
	}
	return true;
}
