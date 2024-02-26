#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <fstream>
#include <string>
#include <map>

#include "State.h"


class Image {
public:
	Image(std::string filepath);
	int width()const;
	int hight()const;
	void drawImage(int y, int x, State::Object o, bool isPlayer)const;
private:
	const int mCellSize = 32;
	enum ImageId {
		IMG_SPACE,
		IMG_WALL,
		IMG_BLOCK,
		IMG_GOAL,
		IMG_PLAYER,
	};
	const std::map<ImageId, std::pair<int, int>> mSubImagePos = {
		{IMG_SPACE, {0 * mCellSize,0*mCellSize}},
		{IMG_WALL, {0 * mCellSize,1*mCellSize}},
		{IMG_BLOCK, {0 * mCellSize,2*mCellSize}},
		{IMG_GOAL, {0 * mCellSize,3*mCellSize}},
		{IMG_PLAYER, {0 * mCellSize,4*mCellSize}} };
	unsigned getUnsignedBE(std::ifstream& ifs)const;
	unsigned getUnsignedLE(std::ifstream& ifs)const;
	unsigned mHight;
	unsigned mWidth;
	std::vector<std::vector<unsigned >> mImage;
	void drawSubImage(int dY, int dX, const std::vector<ImageId>& stack)const;
	unsigned alphaBlend(unsigned a, unsigned b)const;
};
#endif // IMAGE_H
