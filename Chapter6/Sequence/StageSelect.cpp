#include "Sequence/StageSelect.h"
#include "Image.h"
#include "GameLib/Framework.h"

bool getNumKey(unsigned& stage) {
	
	if (GameLib::Framework::instance().isKeyTriggered('0')) {
		stage = 0;
		return true;
	}
	else if (GameLib::Framework::instance().isKeyTriggered('1')) {
		stage = 1;
		return true;
	}
	else if (GameLib::Framework::instance().isKeyTriggered('2')) {
		stage = 2;
		return true;
	}
	else if (GameLib::Framework::instance().isKeyTriggered('3')) {
		stage = 3;
		return true;
	}
	else if (GameLib::Framework::instance().isKeyTriggered('4')) {
		stage = 4;
		return true;
	}
	else if (GameLib::Framework::instance().isKeyTriggered('5')) {
		stage = 5;
		return true;
	}
	else if (GameLib::Framework::instance().isKeyTriggered('6')) {
		stage = 6;
		return true;
	}
	else if (GameLib::Framework::instance().isKeyTriggered('7')) {
		stage = 7;
		return true;
	}
	else if (GameLib::Framework::instance().isKeyTriggered('8')) {
		stage = 8;
		return true;
	}
	else if (GameLib::Framework::instance().isKeyTriggered('9')) {
		stage = 9;
		return true;
	}
	return false;
}

namespace Sequence {
	int getInput() {
		if (GameLib::Framework::instance().isKeyTriggered('w')) {
			return -1;
		}
		else if (GameLib::Framework::instance().isKeyTriggered('z')) {
			return 1;
		}
		return 0;
	}
	StageSelect::StageSelect():
		mSeq(SeqId::SEQ_STAGE_SELECT),
		mStageSelectImagePtr(new StageSelectImage("data/image/stageSelect.dds")),
		mSelectedStage(0)
	{}
	StageSelect::SeqId StageSelect::update(unsigned& stage) {
		SeqId next = mSeq;
		switch (mSeq) {
		case SeqId::SEQ_STAGE_SELECT:
			mSelectedStage = (mSelectedStage + getInput() + 9) % 9;
			if (GameLib::Framework::instance().isKeyTriggered(' ')) {
				stage = mSelectedStage+1;
				next = SeqId::SEQ_END;
			}
			mStageSelectImagePtr->drawImage(0, 0, StageSelectImage::Id::IMG_STAGE_SELECT);
			{
				FontImage& font = FontImage::instance();
				font.drawString(0, 0, "[STAGE]");
				
				for (int i = 0; i < 9; i++) {
					font.drawString(i+1, 1, "STAGE "+ std::to_string(i+1), true, i == mSelectedStage ? 0xffffff : 0x777777);
				}
			}
			break;
		default:
			break;

		}

		return mSeq = next;
	}
}