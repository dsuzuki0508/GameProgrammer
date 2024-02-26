#include "Sequence/Game/Result.h"
#include "Image.h"
#include "GameLib/Framework.h"
#include "Game/State.h"
using namespace std;
namespace Sequence {
	namespace Game {
		Result::Result(unique_ptr<State>& state_ptr) :
			mSeq(SeqId::SEQ_RESULT),
			mCountMSec(1000),
			mStatePtr(state_ptr),
			mCellsImagePtr(new CellsImage("data/image/image2.dds"))
		{}
		Result::SeqId Result::update() {
			static GameLib::Framework f = GameLib::Framework::instance();
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_RESULT:
				mStatePtr->draw();
				f.drawDebugString(1, 1, "RESULT", 0xff000000);
				if (mStatePtr->isAlive1P()) {
					f.drawDebugString(1, 2, "1P WIN", 0xff000000);
				}
				else if (mStatePtr->isAlive2P()){
					f.drawDebugString(1, 2, "2P WIN", 0xff000000);
				}
				mCountMSec -= min(mCountMSec, (unsigned)GameLib::Framework::instance().previousFrameInterval());
				if (mCountMSec == 0)next = SeqId::SEQ_END;
				break;
			default:
				break;
			}

			return mSeq = next;
		}
	}
}