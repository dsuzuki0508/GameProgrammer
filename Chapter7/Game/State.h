#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <memory>

#include "Image.h"
#include "Game/StaticObject.h"
#include "Game/DynamicObject.h"
#include "Game/Move.h"
class State {
public:
	State(unsigned stage_id);
	void update(const Move& m);
	void draw()const;
	bool hasCleared() const;
	bool isAlive1P()const;
	bool isAlive2P()const;
#ifndef NDEBUG
	unsigned mWinner;
#endif

private:
	const std::unique_ptr<CellsImage> mCellsImagePtr;
	std::vector<std::vector<StaticObject>> mStaticObjects;
	std::vector<DynamicObject> mDynamicObjects;
	unsigned mStageId;

};

#endif // GAME_STATE_H