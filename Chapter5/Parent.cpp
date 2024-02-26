#include "Sequence/Parent.h"
#include "Sequence/Title.h"
#include "Sequence/StageSelect.h"
#include "Sequence/Game/Parent.h"

using namespace std;

namespace Sequence {
	Parent::Parent():
		mSeq(SeqId::SEQ_TITLE) 
	{}
	Parent::SeqId Parent::update() {
		SeqId next = mSeq;
		switch (mSeq) {
		case SeqId::SEQ_TITLE:
			if (!mTitlePtr)mTitlePtr.reset(new Title());
			{
				auto tmp = mTitlePtr->update();
				if (tmp == Title::SeqId::SEQ_END)next = SeqId::SEQ_STAGE_SELECT;
			}
			break;
		case SeqId::SEQ_STAGE_SELECT:
			if (!mStageSelectPtr)mStageSelectPtr.reset(new StageSelect());
			{
				auto tmp = mStageSelectPtr->update(mStage);
				if (tmp == StageSelect::SeqId::SEQ_END)next = SeqId::SEQ_GAME;
			}
			break;
		case SeqId::SEQ_GAME:
			if (!mGamePtr)mGamePtr.reset(new Game::Parent(mStage));
			{
				auto tmp = mGamePtr->update();
				if (tmp == Game::Parent::SeqId::SEQ_TO_TITLE)next = SeqId::SEQ_TITLE;
				if (tmp == Game::Parent::SeqId::SEQ_TO_STAGE_SELECT)next = SeqId::SEQ_STAGE_SELECT;
				if (tmp == Game::Parent::SeqId::SEQ_END)next = SeqId::SEQ_TITLE;
			}
			break;
		default:
			next = SeqId::SEQ_TITLE;
		}
		if (next != mSeq) {
			mTitlePtr.reset();
			mStageSelectPtr.reset();
			mGamePtr.reset();
		}
		return mSeq = next;
	}
}