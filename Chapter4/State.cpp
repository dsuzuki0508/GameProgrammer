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
template <typename T, typename U>
std::pair<T, U> operator*(const std::pair<T, U>& l, const unsigned r) {
	return { l.first * r,l.second * r };
}
template <typename T, typename U>
std::pair<T, U> operator/(const std::pair<T, U>& l, const unsigned r) {
	return { l.first / r,l.second / r };
}

State::State(const char* stageData, unsigned size) {
	vector<unsigned> tmp;
	int tmpPlayer = 0;
	for (unsigned i = 0; i < size; i++) {
		switch (stageData[i]) {
		case ' ':
			tmp.push_back(OBJ_SPACE);
			break;
		case '#':
			tmp.push_back(OBJ_WALL);
			break;
		case 'o':
			tmp.push_back(OBJ_BLOCK|OBJ_SPACE);
			break;
		case '.':
			tmp.push_back(OBJ_GOAL|OBJ_SPACE);
			break;
		case 'p':
			mPlayer.first = static_cast<unsigned>(mMap.size());
			mPlayer.second = static_cast<unsigned>(tmp.size());
			tmp.push_back(OBJ_SPACE);
			break;
		case 'P':
			mPlayer.first = static_cast<unsigned>(mMap.size());
			mPlayer.second = static_cast<unsigned>(tmp.size());
			tmp.push_back(OBJ_GOAL|OBJ_SPACE);
			break;
		case 'O':
			tmp.push_back(OBJ_BLOCK | OBJ_GOAL | OBJ_SPACE);
			break;
		case '\n':
			if (tmp.size())mMap.push_back(tmp);
			tmp.clear();
		default:
			break;
		}
	}
	if (tmp.size())mMap.push_back(tmp);

	unsigned w = mMap[0].size();
	for (unsigned i = 0; i < mMap.size(); i++) {
		assert(mMap[i].size() == w);
	}
	mHight = mMap.size();
	mWidth = w;

}

void State::update(const Move& move) {
	//for (int i = 0; i < mMap.size(); i++) {
	//	for (int j = 0; j < mMap[i].size(); j++) {
	//		char c = ' ';
	//		switch (mMap[i][j]) {
	//		case OBJ_WALL:
	//			c = '#'; break;
	//		case OBJ_GOAL:
	//			c = '.'; break;
	//		case OBJ_BLOCK:
	//			c = 'o'; break;
	//		case OBJ_GOAL | OBJ_BLOCK:
	//			c = 'O'; break;
	//		case OBJ_SPACE:
	//		default:
	//			break;
	//		}
	//		if (mPlayer == make_pair(i, j)) {
	//			if (mMap[i][j] & OBJ_GOAL) {
	//				c = 'P';
	//			}
	//			else {
	//				c = 'p';
	//			}
	//		}
	//		GameLib::cout << c;
	//	}
	//	GameLib::cout << GameLib::endl;
	//}
	//GameLib::cout << "<" << move.dy() << "," << move.dx() << ">" << GameLib::endl;
	static unsigned previous_time = GameLib::Framework::instance().time();
	static unsigned now = GameLib::Framework::instance().time();
	previous_time = now;
	now = GameLib::Framework::instance().time();
	if (now - previous_time < (1000 / MAX_FRAME_RATE)) {
		GameLib::Framework::instance().sleep((1000 / MAX_FRAME_RATE) - (now - previous_time));
		now = GameLib::Framework::instance().time();
	}

	if (mAnimations.size() > 0) {
		for (auto it = mAnimations.begin(); it != mAnimations.end();) {
			it->move(now - previous_time);
			if (it->hasCompleted()) {
				if (isPlayer(it->image())) {
					mPlayer = it->point() / Image::cellSize;
				}
				else {
					pair<unsigned, unsigned> tmpp = it->point()/Image::cellSize;
					mMap[tmpp.first][tmpp.second] |= imageToObject(it->image());
				}
				it = mAnimations.erase(it);
			}
			else {
				it++;
			}
		}
		return;

	}
	if (move.d() == make_pair(0, 0))return;
	pair<int, int> next = mPlayer + move.d();
	if (next.first < 0 || mHight <= next.first || next.second < 0 || mWidth <= next.second) return;
	if (mMap[next.first][next.second] & OBJ_WALL) return;
	if (mMap[next.first][next.second] & OBJ_BLOCK) {
		auto tmp = next + move.d();
		if (tmp.first < 0 || mHight <= tmp.first || tmp.second < 0 || mWidth <= tmp.second) return;
		if (!(mMap[tmp.first][tmp.second] & (OBJ_SPACE | OBJ_GOAL))) {
			return;
		}
		mAnimations.push_back(Animation(next * Image::cellSize, objectToImage(OBJ_BLOCK), move.d()));
		mMap[next.first][next.second] &= OBJ_GOAL;
		mMap[next.first][next.second] |= OBJ_SPACE;
	}
	assert(mMap[next.first][next.second] | OBJ_SPACE);
//	mPlayer = next;
	mAnimations.push_back(Animation(mPlayer * Image::cellSize, Image::IMG_PLAYER,  move.d()));
	mPlayer = { -1,-1 };

}
void State::draw(const unique_ptr<Image>& image_ptr)const {
	for (int i = 0; i < mHight; i++) {
//		GameLib::cout << i << " ";
		for (int j = 0; j < mWidth; j++) {
//			GameLib::cout << " " << j;
			//char c;
			//if (mMap[i][j] & OBJ_GOAL) {
			//	if (mPlayer == make_pair(i, j)) {
			//		GameLib::cout << 'P';
			//	}
			//	else if (mMap[i][j] & OBJ_BLOCK) {
			//		GameLib::cout << 'O';
			//	}
			//	else {
			//		GameLib::cout << '.';
			//	}
			//}
			//else {
			//	if (mPlayer == make_pair(i, j)) {
			//		GameLib::cout << 'p';
			//	}
			//	else {
			//		switch (mMap[i][j]&0x7) {
			//		case OBJ_SPACE:GameLib::cout << ' '; break;
			//		case OBJ_WALL:GameLib::cout << '#'; break;
			//		case OBJ_BLOCK | OBJ_SPACE:
			//		case OBJ_BLOCK:GameLib::cout << 'o'; break;
			//		}
			//	}
			//}


			if (mMap[i][j] & OBJ_WALL) {
				image_ptr->drawImage(i * Image::cellSize, j * Image::cellSize, objectToImage(OBJ_WALL));
			}
			else {
				if (mMap[i][j] & OBJ_SPACE) {
					image_ptr->drawImage(i * Image::cellSize, j * Image::cellSize, objectToImage(OBJ_SPACE));
				}
				if (mMap[i][j] & OBJ_GOAL) {
					image_ptr->drawImage(i * Image::cellSize, j * Image::cellSize, objectToImage(OBJ_GOAL));
				}
				if (mMap[i][j] & OBJ_BLOCK) {
					image_ptr->drawImage(i * Image::cellSize, j * Image::cellSize, objectToImage(OBJ_BLOCK));
				}
				if (mPlayer == make_pair(i, j)) {
					image_ptr->drawImage(i * Image::cellSize, j * Image::cellSize, Image::IMG_PLAYER);
				}
			}
		}
		//GameLib::cout << GameLib::endl;
	}
	for (const auto& e : mAnimations) {
		image_ptr->drawImage(e.point().first, e.point().second, e.image());
	}
	image_ptr->flush();

//	image_ptr->drawImage(mMap, mPlayer, mAnimations);
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

State::Animation::Animation(const std::pair<int, int>& point, Image::ImageId image, const std::pair<int, int>& direction, unsigned epoch):
mImage(image),
mDirection(direction),
mPoint(point),
mEpoch(epoch){
	mMiliSec = 1000 * mEpoch / EPOCH_PAR_SECOND;
}
bool State::Animation::hasCompleted()const {
	return mEpoch <= 0 && mMiliSec <= 0;
}
void State::Animation::move(unsigned m_sec) {
	m_sec = min(m_sec, mMiliSec);
	mMiliSec -= m_sec;
	unsigned new_epoch = mMiliSec * EPOCH_PAR_SECOND / 1000;
	mPoint = mPoint + mDirection * (mEpoch - new_epoch);
	mEpoch = new_epoch;
}
std::pair<int, int> State::Animation::point()const {
	return mPoint;
}
Image::ImageId State::Animation::image()const {
	return mImage;
}
bool State::isPlayer(Image::ImageId image){
	return image == Image::IMG_PLAYER;
}

State::Object State::imageToObject(Image::ImageId image) {
	switch (image) {
	case Image::IMG_BLOCK:
		return OBJ_BLOCK;
	case Image::IMG_GOAL:
		return OBJ_GOAL;
	case Image::IMG_SPACE:
		return OBJ_SPACE;
	case Image::IMG_WALL:
		return OBJ_WALL;
	case Image::IMG_UNKNOWN:
		return OBJ_UNKNOWN;
	default:
		return OBJ_UNKNOWN;
	}
}
Image::ImageId State::objectToImage(Object object) {
	switch (object) {
	case OBJ_BLOCK:
		return Image::IMG_BLOCK;
	case OBJ_GOAL:
		return Image::IMG_GOAL;
	case OBJ_SPACE:
		return Image::IMG_SPACE;
	case OBJ_WALL:
		return Image::IMG_WALL;
	case OBJ_UNKNOWN:
		return Image::IMG_UNKNOWN;
	default:
		return Image::IMG_UNKNOWN;
	}
}