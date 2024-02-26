#ifndef PAD_H
#define PAD_H
class Pad
{
public:
	enum class Button {
		A,
		B,
		U,
		D,
		L,
		R,
		Q,
	};
	static bool isOn(Button, int playerId = 0);
	static bool isTriggered(Button, int playerId = 0);
};

#endif // PAD_H
