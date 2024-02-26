#ifndef GAME_MOVE_H
#define GAME_MOVE_H
#include <utility>


class Move {
public:
	Move();
	Move(const char c);
	int dy()const;
	int dx() const;
	std::pair<int, int> d()const;
	bool hasEndRequested();
	bool hasMenuRequested();
	bool operator == (const Move& r);
	bool operator != (const Move& r);
private:
	std::pair<int, int> m = { 0,0 };
	bool mEndReq = false;
	bool mMenuReq = false;
};


#endif // GAME_MOVE_H
