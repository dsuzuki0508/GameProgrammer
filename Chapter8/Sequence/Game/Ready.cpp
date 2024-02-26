#include "Sequence/Game/Ready.h"
#include "Image.h"
#include "GameLib/Framework.h"
using namespace std;
namespace Sequence {
	namespace Game {
		Ready::Ready(unique_ptr<State>& state_ptr, unsigned stage_id) :
			mStatePtr(state_ptr),
			mSeq(SeqId::SEQ_READY),
			mLoadingImagePtr(new LoadingImage("data/image/loading.dds")),
			mCountMSec(3000),
			mStageId(stage_id)
		{
			mStatePtr.reset();
		}
		Ready::SeqId Ready::update() {
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_READY:
				mLoadingImagePtr->drawImage(0, 0, LoadingImage::Id::IMG_LOADING);
				if (mCountMSec != 1000 && !mStatePtr) {

					mStatePtr.reset(new State(mStageId));
				}
				mCountMSec -= min(mCountMSec, (unsigned)GameLib::Framework::instance().previousFrameInterval());
				if (mCountMSec == 0 && mStatePtr)next = SeqId::SEQ_END;
				break;
			default:
				break;
			}

			return mSeq = next;
		}
	}
}