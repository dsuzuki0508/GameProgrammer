#include "Image.h"

#include <assert.h>
#include "State.h"
#include "GameLib/Framework.h"

using namespace std;

unsigned Image::getUnsignedLE(ifstream& ifs)const {
	unsigned ret = 0;
	for (int i = 0; i < 32; i += 8) {
		char tmp;
		ifs.read(&tmp, 1);
		ret += (static_cast<unsigned>(static_cast<unsigned char>(tmp)) << i);
	}
	return ret;
}
unsigned Image::getUnsignedBE(ifstream& ifs)const {
	unsigned ret = 0;
	for (int i = 0; i < 4; i++) {
		char tmp;
		ifs.read(&tmp, 1);
		ret <<= 8;
		ret += static_cast<unsigned>(tmp);
	}
	return ret;
}

Image::Image(string filepath) {

	ifstream ifs(filepath, ifstream::binary);
	ifs.seekg(0, ifstream::end);
	int size = static_cast<int>(ifs.tellg()) - 128;

	ifs.seekg(12, ifstream::beg);
	mHight = getUnsignedLE(ifs);
	ifs.seekg(16, ifstream::beg);
	mWidth = getUnsignedLE(ifs);
	assert(mHight * mWidth <= size);

	ifs.seekg(128, ifstream::beg);
	for (int i = 0; i < mHight; i++) {
		vector<unsigned> tmp;
		for (int j = 0; j < mWidth; j++) {
			tmp.push_back(getUnsignedLE(ifs));
		}
		mImage.push_back(tmp);
	}

}

int Image::width()const {
	return mWidth;
};
int Image::hight()const {
	return mHight;
};

unsigned Image::alphaBlend(unsigned a, unsigned b)const {
	unsigned alpha = (b >> 24) & 0xff;
	unsigned ret = a & 0xff000000;
	for (int i = 0; i < 3; i++) {
		unsigned mask = 0xff << (i * 8);
		unsigned ac = a & mask;
		unsigned bc = b & mask;
		unsigned tmp = (bc - ac) * alpha / 255 + ac;
		ret += (tmp & mask);
	}
	return ret;
}

void Image::drawSubImage(int dY, int dX, const vector<ImageId>& stack)const {
	unsigned* vram = GameLib::Framework::instance().videoMemory();
	int windowsWidth = GameLib::Framework::instance().width();

	for (int i = 0; i < mCellSize; i++) {
		for (int j = 0; j < mCellSize; j++) {
			unsigned dot = 0x00000000;
			for (int k = 0; k < stack.size(); k++) {
				int sX = mSubImagePos.at(stack[k]).first + i;
				int sY = mSubImagePos.at(stack[k]).second + j;
				dot = alphaBlend(dot, mImage[sX][sY]);
			}
			vram[(dY + i) * windowsWidth + (dX + j)] = dot;
		}
	}
}
void Image::drawImage(int y, int x, State::Object o, bool isPlayer)const {
	vector<ImageId> stack;
	if (!(o & State::OBJ_WALL)) {
		stack.push_back(IMG_SPACE);
		if (o & State::OBJ_GOAL) {
			stack.push_back(IMG_GOAL);
		}
	}
	if (isPlayer) {
		stack.push_back(IMG_PLAYER);
	}
	else {
		switch (o&0x7)
		{
		case State::OBJ_WALL:
			stack.push_back(IMG_WALL);
			break;
		case State::OBJ_BLOCK:
			stack.push_back(IMG_BLOCK);
			break;
		case State::OBJ_UNKNOWN:
		default:
			break;
		}
	}
	drawSubImage(y*mCellSize, x*mCellSize, stack);
}