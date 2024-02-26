#include "Image.h"

#include <assert.h>
#include "State.h"
#include "GameLib/Framework.h"

using namespace std;


unsigned getUnsignedLE(ifstream& ifs) {
	unsigned ret = 0;
	for (int i = 0; i < 32; i += 8) {
		char tmp;
		ifs.read(&tmp, 1);
		ret += (static_cast<unsigned>(static_cast<unsigned char>(tmp)) << i);
	}
	return ret;
}


unsigned getUnsignedBE(ifstream& ifs) {
	unsigned ret = 0;
	for (int i = 0; i < 4; i++) {
		char tmp;
		ifs.read(&tmp, 1);
		ret <<= 8;
		ret += static_cast<unsigned>(tmp);
	}
	return ret;
}

template<typename T>
void Image<T>::fill(unsigned color) {
	unsigned* vram = GameLib::Framework::instance().videoMemory();
	unsigned window_height = GameLib::Framework::instance().height();
	unsigned window_width = GameLib::Framework::instance().width();
	for (int i = 0; i < window_height*window_width; i++) {
		vram[i] = color;

	}
}


template<typename T>
Image<T>::Image(const string& filepath) {

	ifstream ifs(filepath, ifstream::binary);
	ifs.seekg(0, ifstream::end);
	unsigned size = static_cast<unsigned>(ifs.tellg()) - 128;

	ifs.seekg(12, ifstream::beg);
	mHeight = getUnsignedLE(ifs);
	ifs.seekg(16, ifstream::beg);
	mWidth = getUnsignedLE(ifs);
	assert(mHeight * mWidth <= size);

	ifs.seekg(128, ifstream::beg);
	for (unsigned i = 0; i < mHeight; i++) {
		vector<unsigned> tmp(mWidth);
		for (auto& e : tmp) {
			e = getUnsignedLE(ifs);
		}
		mImage.push_back(tmp);
	}
}

template<typename T>
unsigned Image<T>::width()const {
	return mWidth;
};

template<typename T>
unsigned Image<T>::height()const {
	return mHeight;
};


unsigned alphaBlend(unsigned a, unsigned b) {
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

template<typename T>
void Image<T>::drawImage(unsigned y, unsigned x, const image_defines::Plot& p, bool use_color, unsigned color) {
	unsigned* vram = GameLib::Framework::instance().videoMemory();
	unsigned window_height = GameLib::Framework::instance().height();
	unsigned window_width = GameLib::Framework::instance().width();
	for (int i = 0; i < p.heigth; i++) {
		unsigned dy = y + i;
		unsigned sy = p.y + i;
		if (dy >= window_height)break;
		if (sy >= mHeight)break;
		for (int j = 0; j < p.width; j++) {
			unsigned dx = x + j;
			unsigned sx = p.x + j;
			if (dx >= window_width)break;
			if (sx >= mWidth)break;

			unsigned* dest = &vram[dy * window_width + dx];

			if (!use_color) {
				*dest = alphaBlend(*dest, mImage[sy][sx]);
			}
			else {
				unsigned mask = 0xff;
				unsigned tmp1 = ((mImage[sy][sx] & mask) + ((mImage[sy][sx] >> 8) & mask) + ((mImage[sy][sx] >> 16) & mask))/3;
				unsigned B = (color >> 0) & mask;
				unsigned G = (color >> 8) & mask;
				unsigned R = (color >> 16) & mask;
				B = B * tmp1 / 255;
				B &= mask; mask << 8;
				G = G * tmp1 / 255;
				G &= mask; mask << 8;
				R = R * tmp1 / 255;
				R &= mask;
				*dest = alphaBlend(*dest, (R<<16) | (G << 8) | B | (mImage[sy][sx] & 0xff000000));
			}

		}
	}
}
template<typename T>
void Image<T>::drawImage(unsigned y, unsigned x, typename T::Id image_id, bool use_color, unsigned color) {
	image_defines::Plot p = T::plots.at(image_id);
	drawImage(y, x, p, use_color, color);
}

FontImage::FontImage(const std::string& filepath) :
	Image<image_defines::Font>(filepath) {}

FontImage::~FontImage() {}
FontImage& FontImage::instance() {
	static FontImage instance("data/image/font.dds");
	return instance;
}
void FontImage::drawChar(unsigned row, unsigned column, char c, bool use_color, unsigned color)  {
	unsigned h = GameLib::Framework::instance().height();
	unsigned w = GameLib::Framework::instance().width();
	if (c < 32 || 128 <= c)return;
	c -= 32;
	unsigned dy = row * 16;
	unsigned dx = column * 8;
	if (dy >= h)return;
	if (dx >= w)return;
	unsigned sy = c / 16 * 16;
	unsigned sx = c % 16 * 8;

	drawImage(dy, dx, { sy,sx,16,8 }, use_color, color);
}
void FontImage::drawString(unsigned row, unsigned column, std::string str, bool use_color, unsigned color)  {
	for (int i = 0; i < str.size(); i++) {
		drawChar(row, column + i, str[i], use_color, color);
	}
}
template class Image<image_defines::Cells>;
template class Image<image_defines::Clear>;
template class Image<image_defines::Loading>;
template class Image<image_defines::Menu>;
template class Image<image_defines::StageSelect>;
template class Image<image_defines::Title>;