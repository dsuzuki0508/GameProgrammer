#ifndef DEFINES_H
#define DEFINES_H

#define MAX_FRAME_RATE 60
#define PIXEL_PAR_SEC 64
#ifndef NDEBUG
struct StageData {
	int mEnemyNumber;
	int mBrickRate;
	int mItemPowerNumber;
	int mItemBombNumber;
};
const static StageData gStageData[] = {
	{2, 90,4, 6},
	{3, 80, 1, 0},
	{6, 30, 0, 1},
};
#define WIDTH 20
#define HEIGHT 15
#endif // !NDEBUG


#endif // DEFINES_H