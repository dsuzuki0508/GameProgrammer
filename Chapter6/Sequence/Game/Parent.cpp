#include "Sequence/Game/Parent.h"
#include "GameLib/Framework.h"

using namespace std;

namespace Sequence {
	namespace Game {
		Parent::Parent( unsigned stage):
			mSeq(SeqId::SEQ_LOAD),
			mStage(stage)
		{}
		Parent::SeqId Parent::update() {
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_LOAD:
				if (!mLoadPtr)mLoadPtr.reset(new Load(mStatePtr, mStage));
				{
					auto tmp = mLoadPtr->update();
					if (tmp == Load::SeqId::SEQ_END)next = SeqId::SEQ_PLAY;
				}
				break;
			case SeqId::SEQ_PLAY:
				if (!mPlayPtr)mPlayPtr.reset(new Play(mStatePtr));
				{
					auto tmp = mPlayPtr->update();
					if (tmp == Play::SeqId::SEQ_END)next = SeqId::SEQ_CLEAR;
					if (tmp == Play::SeqId::SEQ_TO_MENU)next = SeqId::SEQ_MENU;
				}
				break;
			case SeqId::SEQ_MENU:
				if (!mMenuPtr)mMenuPtr.reset(new Menu(mStatePtr));
				{
					auto tmp = mMenuPtr->update();
					if (tmp == Menu::SeqId::SEQ_TO_LOAD)next = SeqId::SEQ_LOAD;
					if (tmp == Menu::SeqId::SEQ_TO_STAGE_SELECT)next = SeqId::SEQ_TO_STAGE_SELECT;
					if (tmp == Menu::SeqId::SEQ_TO_TITLE)next = SeqId::SEQ_TO_TITLE;
					if (tmp == Menu::SeqId::SEQ_END)next = SeqId::SEQ_PLAY;

				}
				break;
			case SeqId::SEQ_CLEAR:
				if (!mClearPtr)mClearPtr.reset(new Clear(mStatePtr));
				{
					auto tmp = mClearPtr->update();
					if (tmp == Clear::SeqId::SEQ_END) {
						mStatePtr.reset();
						next = SeqId::SEQ_TO_STAGE_SELECT;
					}
				}
				break;
			default:
				next = SeqId::SEQ_TO_STAGE_SELECT;
			}
			if (next != mSeq) {
				mLoadPtr.reset();
				mPlayPtr.reset();
				mMenuPtr.reset();
//				mClearPtr.reset();
			}
			return mSeq = next;
		}
	}
}