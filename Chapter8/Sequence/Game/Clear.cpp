#include "Sequence/Game/Clear.h"
#include "Image.h"
#include "GameLib/Framework.h"

using namespace std;
namespace Sequence {
	namespace Game {
		Clear::Clear(unique_ptr<State>& state_ptr) :
			mSeq(SeqId::SEQ_CLEAR),
			mClearImagePtr(new ClearImage("data/image/clear.dds")),
			mCountMSec(3000),
			mStatePtr(state_ptr)
		{}
		Clear::SeqId Clear::update() {
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_CLEAR:
				mStatePtr->draw();
				mClearImagePtr->drawImage(0, 0, ClearImage::Id::IMG_CLEAR);
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