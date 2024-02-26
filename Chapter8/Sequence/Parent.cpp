#include "Sequence/Parent.h"
#include "Sequence/Title.h"
#include "Sequence/GameOver.h"
#include "Sequence/Ending.h"
#include "Sequence/Game/Parent.h"

using namespace std;

namespace Sequence {
	Parent::Parent() :
		mSeq(SeqId::SEQ_TITLE)
	{}
	Parent::SeqId Parent::update() {
		SeqId next = mSeq;
		switch (mSeq) {
		case SeqId::SEQ_TITLE:
			if (!mTitlePtr)mTitlePtr.reset(new Title());
			{
				auto tmp = mTitlePtr->update();
				if (tmp == Title::SeqId::SEQ_TO_GAME_SOLO)next = SeqId::SEQ_GAME_SOLO;
				if (tmp == Title::SeqId::SEQ_TO_GAME_DUO)next = SeqId::SEQ_GAME_DUO;
			}
			break;
		case SeqId::SEQ_GAME_SOLO:
		case SeqId::SEQ_GAME_DUO:
			if (!mGamePtr)mGamePtr.reset(new Game::Parent(mSeq==SeqId::SEQ_GAME_DUO?0:1));
			{
				auto tmp = mGamePtr->update();
				if (tmp == Game::Parent::SeqId::SEQ_TO_TITLE)next = SeqId::SEQ_TITLE;
				if (tmp == Game::Parent::SeqId::SEQ_TO_GAME_OVER)next = SeqId::SEQ_GAME_OVER;
				if (tmp == Game::Parent::SeqId::SEQ_TO_ENDING)next = SeqId::SEQ_ENDING;
			}
			break;
		case SeqId::SEQ_GAME_OVER:
			if (!mGameOverPtr)mGameOverPtr.reset(new GameOver());
			{
				auto tmp = mGameOverPtr->update();
				if (tmp == GameOver::SeqId::SEQ_END)next = SeqId::SEQ_TITLE;
			}
			break;
		case SeqId::SEQ_ENDING:
			if (!mEndingPtr)mEndingPtr.reset(new Ending());
			{
				auto tmp = mEndingPtr->update();
				if (tmp == Ending::SeqId::SEQ_END)next = SeqId::SEQ_TITLE;
			}
			break;
		default:
			next = SeqId::SEQ_TITLE;
		}
		if (next != mSeq) {
			mTitlePtr.reset();
			mGamePtr.reset();
			mGameOverPtr.reset();
			mEndingPtr.reset();
		}
		return mSeq = next;
	}
}