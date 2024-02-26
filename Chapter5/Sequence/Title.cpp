#include "Sequence/Title.h"
#include "Image.h"
#include "GameLib/Framework.h"
namespace Sequence {
	Title::Title():
		mSeq(SeqId::SEQ_TITLE),
		mTitleImagePtr(new TitleImage("title.dds"))
	{}
	Title::SeqId Title::update() {
		SeqId next = mSeq;
		switch (mSeq) {
		case SeqId::SEQ_TITLE:
			if (GameLib::Framework::instance().isKeyTriggered(' ')) {
				next = SeqId::SEQ_END;
			}
			mTitleImagePtr->drawImage(0, 0, TitleImage::Id::IMG_TITLE);
			break;
		default:
			break;
		}
		return mSeq = next;
	}
}