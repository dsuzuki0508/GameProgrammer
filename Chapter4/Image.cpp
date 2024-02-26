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

Image::Image(const string& filepath) {

	ifstream ifs(filepath, ifstream::binary);
	ifs.seekg(0, ifstream::end);
	unsigned size = static_cast<unsigned>(ifs.tellg()) - 128;

	ifs.seekg(12, ifstream::beg);
	mHight = getUnsignedLE(ifs);
	ifs.seekg(16, ifstream::beg);
	mWidth = getUnsignedLE(ifs);
	assert(mHight * mWidth <= size);

	ifs.seekg(128, ifstream::beg);
	for (unsigned i = 0; i < mHight; i++) {
		vector<unsigned> tmp;
		for (unsigned j = 0; j < mWidth; j++) {
			tmp.push_back(getUnsignedLE(ifs));
		}
		mImage.push_back(tmp);
	}

	unsigned window_height = GameLib::Framework::instance().height();
	unsigned window_width  = GameLib::Framework::instance().width();
	mBuf.assign(window_height, vector<unsigned>(window_width, 0));
}

unsigned Image::width()const {
	return mWidth;
};
unsigned Image::hight()const {
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

void Image::drawImage(unsigned y, unsigned x, ImageId image_id) {
	pair<unsigned, unsigned> image_pos = mSubImagePos.at(image_id);
	for (int i = 0; i < mCellSize; i++) {
		for (int j = 0; j < mCellSize; j++) {
			unsigned dy = y + i;
			unsigned dx = x + j;
			unsigned sy = image_pos.first + i;
			unsigned sx = image_pos.second + j;
			if (dy >= GameLib::Framework::instance().height())break;
			if (dx >= GameLib::Framework::instance().width())break;
			if (sy >= mHight)break;
			if (sx >= mWidth)break;

			mBuf[dy][dx] = alphaBlend(mBuf[dy][dx], mImage[sy][sx]);

		}
	}
}
void Image::flush()const {
	unsigned* vram = GameLib::Framework::instance().videoMemory();
	unsigned window_width = GameLib::Framework::instance().width();
	for (int i = 0; i < mBuf.size(); i++) {
		for (int j = 0; j < mBuf[i].size(); j++) {
			vram[i * window_width + j] = mBuf[i][j];
		}
	}
}