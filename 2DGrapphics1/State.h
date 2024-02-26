#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>

class Move;
class Image;

class State {
public:
	State(const char* stageData, int size);
	void update(Move& move);
	void draw(const std::unique_ptr<Image>& image_ptr)const;
	bool isClearedState() const;
	std::vector<unsigned>& operator[](int i) { return mMap[i]; }
	enum Object {
		OBJ_SPACE = 0x00000001,
		OBJ_WALL = 0x00000002,
		OBJ_BLOCK = 0x00000004,
		OBJ_GOAL = 0x00000008,
		OBJ_UNKNOWN = 0x80000000,
	};
private:
	void drawCell(int y, int x, unsigned color)const;

	std::vector<std::vector<unsigned>> mMap;
	std::pair<int, int> mPlayer;
	int mWidth;
	int mHight;

};

#endif // STATE_H