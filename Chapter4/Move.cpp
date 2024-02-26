#include "Move.h"

using namespace std;

Move::Move() {}
Move::Move(const char c) {
		switch (c) {
	case 'w':
		m.first = -1;
		break;
	case 'z':
		m.first = 1;
		break;
	case 'a':
		m.second = -1;
		break;
	case 's':
		m.second = 1;
		break;
	case 'q':
		mEndReq = true;
		break;
	default:
		break;
	}
}

int Move::dy()const {
	return m.first;
}

int Move::dx() const {
	return m.second;
}

std::pair<int, int> Move::d()const {
	return m;
}

bool Move::hasEndRequested() {
	return mEndReq;
}
bool Move::operator == (const Move& r) {
	return (m == r.m && mEndReq == r.mEndReq);
}
bool Move::operator != (const Move& r) {
	return !((*this) == r);
}