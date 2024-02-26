#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include <list>

#include "Image.h"

#define EPOCH_PAR_SECOND 64
#define MAX_FRAME_RATE 60

class Move;


class State {
public:
	State(const char* stageData, unsigned size);
	void update(const Move& move);
	void draw(const std::unique_ptr<Image>& image_ptr)const;
	bool isClearedState() const;
	std::vector<unsigned>& operator[](unsigned i) { return mMap[i]; }

private:

	std::vector<std::vector<unsigned>> mMap;
	std::pair<int, int> mPlayer;
	int mWidth;
	int mHight;
	enum Object {
		OBJ_SPACE = 0x00000001,
		OBJ_WALL = 0x00000002,
		OBJ_BLOCK = 0x00000004,
		OBJ_GOAL = 0x00000008,
		OBJ_UNKNOWN = 0x80000000,
	};

	static bool isPlayer(Image::ImageId image);
	static Object imageToObject(Image::ImageId image);
	static Image::ImageId objectToImage(Object object);

	class Animation
	{
	public:
		Animation(const std::pair<int, int>& point, Image::ImageId image, const std::pair<int, int>& direction, unsigned epoch = Image::cellSize);
		bool hasCompleted()const;
		void move(unsigned m_sec = 1000/EPOCH_PAR_SECOND);
		std::pair<int, int> point()const;
		Image::ImageId image()const;
	private:
		Image::ImageId mImage;
		std::pair<int, int> mDirection;
		std::pair<int, int> mPoint;
		unsigned mEpoch;
		unsigned mMiliSec;
	};
	std::list<Animation> mAnimations;
};

#endif // STATE_H