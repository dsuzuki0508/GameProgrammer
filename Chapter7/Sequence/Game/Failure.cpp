#include "Sequence/Game/Failure.h"
#include "Image.h"
#include "GameLib/Framework.h"
#include "Game/State.h"
using namespace std;
namespace Sequence {
	namespace Game {
		Failure::Failure(unique_ptr<State>& state_ptr) :
			mSeq(SeqId::SEQ_FAILURE),
			mCountMSec(1000),
			mStatePtr(state_ptr)
		{}
		Failure::SeqId Failure::update() {
			static GameLib::Framework f = GameLib::Framework::instance();
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_FAILURE:
				mStatePtr->draw();
				f.drawDebugString(1, 1, "FAILURE");
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