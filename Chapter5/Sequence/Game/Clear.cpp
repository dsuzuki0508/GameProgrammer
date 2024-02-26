#include "Sequence/Game/Clear.h"
#include "Image.h"
#include "GameLib/Framework.h"
#include "State.h"
using namespace std;
namespace Sequence {
	namespace Game {
		Clear::Clear(unique_ptr<State>& state_ptr) :
			mSeq(SeqId::SEQ_CLEAR),
			mClearImagePtr(new ClearImage("clear.dds")),
			mCountMSec(1000),
			mStatePtr(state_ptr),
			mCellsImagePtr(new CellsImage("image2.dds"))
		{}
		Clear::SeqId Clear::update() {
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_CLEAR:
				mStatePtr->draw(mCellsImagePtr);
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