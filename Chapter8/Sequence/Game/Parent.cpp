#include "Sequence/Game/Parent.h"
#include "GameLib/Framework.h"

using namespace std;

namespace Sequence {
	namespace Game {
		Parent::Parent( unsigned stage_id):
			mSeq(SeqId::SEQ_READY),
			mStageId(stage_id)
		{}
		Parent::SeqId Parent::update() {
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_READY:
				if (!mReadyPtr)mReadyPtr.reset(new Ready(mStatePtr, mStageId));
				{
					auto tmp = mReadyPtr->update();
					if (tmp == Ready::SeqId::SEQ_END)next = SeqId::SEQ_PLAY;
				}
				break;
			case SeqId::SEQ_PLAY:
				if (!mPlayPtr)mPlayPtr.reset(new Play(mStatePtr));
				{
					auto tmp = mPlayPtr->update();
					if (tmp == Play::SeqId::SEQ_TO_CLEAR)next = SeqId::SEQ_CLEAR;
					if (tmp == Play::SeqId::SEQ_TO_MENU)next = SeqId::SEQ_MENU;
					if (tmp == Play::SeqId::SEQ_TO_FAILURE)next = SeqId::SEQ_FAILURE;
					if (tmp == Play::SeqId::SEQ_TO_RESULT)next = SeqId::SEQ_RESULT;
				}
				break;
			case SeqId::SEQ_MENU:
				if (!mMenuPtr)mMenuPtr.reset(new Menu(mStatePtr));
				{
					auto tmp = mMenuPtr->update();
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
						if (mStageId == 1) {
							mStageId++;
							next = SeqId::SEQ_READY;
						}
						else {
							next = SeqId::SEQ_TO_ENDING;
						}
					}
				}
				break;
			case SeqId::SEQ_FAILURE:
				if (!mFailurePtr)mFailurePtr.reset(new Failure(mStatePtr));
				{
					auto tmp = mFailurePtr->update();
					if (tmp == Failure::SeqId::SEQ_END) {
						mStatePtr.reset();
						next = SeqId::SEQ_TO_GAME_OVER;
					}
				}
				break;
			case SeqId::SEQ_RESULT:
				if (!mResultPtr)mResultPtr.reset(new Result(mStatePtr));
				{
					auto tmp = mResultPtr->update();
					if (tmp == Result::SeqId::SEQ_END) {
						mStatePtr.reset();
						next = SeqId::SEQ_TO_TITLE;
					}
				}
				break;
			default:
				next = SeqId::SEQ_TO_TITLE;
			}
			if (next != mSeq) {
				mReadyPtr.reset();
				mPlayPtr.reset();
				mMenuPtr.reset();
				mClearPtr.reset();
			}
			return mSeq = next;
		}
	}
}