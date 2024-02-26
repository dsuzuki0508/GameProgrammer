#ifndef MOVE_H
#define MOVE_H
#include <utility>


class Move {
public:
	Move(const char c);
	int dy()const;
	int dx() const;
	std::pair<int, int> d()const;
	bool hasEndRequested();
private:
	std::pair<int, int> m = { 0,0 };
	bool mEndReq = false;
};


#endif // MOVE_H
