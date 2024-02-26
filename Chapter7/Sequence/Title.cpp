#include "Sequence/Title.h"
#include "Image.h"
#include "GameLib/Framework.h"

int getInput() {
	if (GameLib::Framework::instance().isKeyTriggered('w')) {
		return -1;
	}
	else if (GameLib::Framework::instance().isKeyTriggered('z')) {
		return 1;
	}
	return 0;
}
namespace Sequence {
	Title::Title():
		mSeq(SeqId::SEQ_TITLE),
		mTitleImagePtr(new TitleImage("data/image/title.dds")),
		mSelectedMode(0)
	{}
	Title::SeqId Title::update() {
		SeqId next = mSeq;
		static GameLib::Framework f = GameLib::Framework::instance();
		switch (mSeq) {
		case SeqId::SEQ_TITLE:
			mSelectedMode = (mSelectedMode + getInput() + 2) % 2;
			if (GameLib::Framework::instance().isKeyTriggered(' ')) {
				if (mSelectedMode == 0)next = SeqId::SEQ_TO_GAME_SOLO;
				if (mSelectedMode == 1)next = SeqId::SEQ_TO_GAME_DUO;
			}
			mTitleImagePtr->drawImage(0, 0, TitleImage::Id::IMG_TITLE, true, 0x333333);
			f.drawDebugString(1, 1, "BAKUDAN-BITO");
			f.drawDebugString(1, 2, "PLAY SOLO", mSelectedMode == 0 ? 0xffffffff : 0xff777777);
			f.drawDebugString(1, 3, "PLAY DUO", mSelectedMode == 1 ? 0xffffffff : 0xff777777);
			break;
		default:
			break;
		}
		return mSeq = next;
	}
}