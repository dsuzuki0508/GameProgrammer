#include "Sequence/Title.h"
#include "Image.h"
#include "GameLib/Framework.h"
namespace Sequence {
	Title::Title():
		mSeq(SeqId::SEQ_TITLE),
		mTitleImagePtr(new TitleImage("data/image/title.dds"))
	{}
	Title::SeqId Title::update() {
		SeqId next = mSeq;
		switch (mSeq) {
		case SeqId::SEQ_TITLE:
			if (GameLib::Framework::instance().isKeyTriggered(' ')) {
				next = SeqId::SEQ_END;
			}
			mTitleImagePtr->drawImage(0, 0, TitleImage::Id::IMG_TITLE, true, 0x333333);
			FontImage::instance().drawString(7, 13, "[NIMOTSU-KUN]");
			FontImage::instance().drawString(8, 14, "Press Space");

			break;
		default:
			break;
		}
		return mSeq = next;
	}
}