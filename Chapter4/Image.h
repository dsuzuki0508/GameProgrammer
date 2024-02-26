#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <fstream>
#include <string>
#include <map>

class Image {
public:
	Image(const std::string& filepath);
	unsigned width()const;
	unsigned hight()const;
	enum ImageId {
		IMG_SPACE,
		IMG_WALL,
		IMG_BLOCK,
		IMG_GOAL,
		IMG_PLAYER,
		IMG_UNKNOWN,
	};
	void drawImage(unsigned y, unsigned x, ImageId image_id);
	void flush()const;
	static const unsigned cellSize = 32;
private:
	unsigned getUnsignedBE(std::ifstream& ifs)const;
	unsigned getUnsignedLE(std::ifstream& ifs)const;
	unsigned alphaBlend(unsigned a, unsigned b)const;

	static const unsigned mCellSize = 32;
	const std::map<ImageId, std::pair<unsigned, unsigned>> mSubImagePos = {
		{IMG_SPACE,  {0 * mCellSize,0 * mCellSize}},
		{IMG_WALL,   {0 * mCellSize,1 * mCellSize}},
		{IMG_BLOCK,  {0 * mCellSize,2 * mCellSize}},
		{IMG_GOAL,   {0 * mCellSize,3 * mCellSize}},
		{IMG_PLAYER, {0 * mCellSize,4 * mCellSize}} };
	unsigned mHight;
	unsigned mWidth;
	std::vector<std::vector<unsigned >> mImage;
	std::vector<std::vector<unsigned>> mBuf;
};

#endif // IMAGE_H
