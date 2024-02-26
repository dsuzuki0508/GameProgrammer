#include "Sequence/Title.h"
#include "Image.h"
#include "GameLib/Framework.h"
#include "Pad.h"

int getInput() {
	if (Pad::isTriggered(Pad::Button::U)) {
		return -1;
	}
	else if (Pad::isTriggered(Pad::Button::D)) {
		return 1;
	}
	return 0;
}
namespace Sequence {
	Title::Title():
		mTitleImagePtr(new TitleImage("data/image/title.dds")),
		mSelectedMode(0)
	{}
	Base* Title::update(std::shared_ptr<Parent> parent)
	{
		Base* next = this;
		static GameLib::Framework f = GameLib::Framework::instance();

		mSelectedMode = (mSelectedMode + getInput() + 2) % 2;
		if (Pad::isTriggered(Pad::Button::A)) {
			static Parent::GameMode game_mode[2] = { Parent::GameMode::MODE_SOLO, Parent::GameMode::MODE_DUO };
			parent->setGameMode(game_mode[mSelectedMode]);
			next = new Game::Parent();
		}
		mTitleImagePtr->drawImage(0, 0, TitleImage::Id::IMG_TITLE, true, 0x333333);
		f.drawDebugString(1, 1, "BAKUDAN-BITO");
		f.drawDebugString(1, 2, "PLAY SOLO", mSelectedMode == 0 ? 0xffffffff : 0xff777777);
		f.drawDebugString(1, 3, "PLAY DUO", mSelectedMode == 1 ? 0xffffffff : 0xff777777);

		return next;
	}
}