#include "Sequence/Ending.h"
#include "GameLib/Framework.h"
#include <algorithm>
using namespace std;
namespace Sequence {
	Ending::Ending():
		mSeq(SeqId::SEQ_ENDING),
		mCountMSec(1000)
	{}
	Ending::SeqId Ending::update() {
		SeqId next = mSeq;
		static GameLib::Framework f = GameLib::Framework::instance();
		switch (mSeq) {
		case SeqId::SEQ_ENDING:
			mCountMSec -= min(mCountMSec, static_cast<unsigned>(f.previousFrameInterval()));
			if (mCountMSec==0) {
				next = SeqId::SEQ_END;
			}
			f.drawDebugString(1, 1, "ENDING");
			break;
		default:
			break;

		}
		return mSeq = next;
	}
}