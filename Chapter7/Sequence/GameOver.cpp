#include "Sequence/GameOver.h"
#include "GameLib/Framework.h"
#include <algorithm>
using namespace std;
namespace Sequence {
	GameOver::GameOver():
		mSeq(SeqId::SEQ_GAMEOVER),
		mCountMSec(1000)
	{}
	GameOver::SeqId GameOver::update() {
		SeqId next = mSeq;
		static GameLib::Framework f = GameLib::Framework::instance();
		switch (mSeq) {
		case SeqId::SEQ_GAMEOVER:
			mCountMSec -= min(mCountMSec, static_cast<unsigned>(f.previousFrameInterval()));
			if (mCountMSec==0) {
				next = SeqId::SEQ_END;
			}
			f.drawDebugString(1, 1, "GAME OVER");
			break;
		default:
			break;

		}
		return mSeq = next;
	}
}