#include "Sequence/Game/Parent.h"
#include "GameLib/Framework.h"

using namespace std;

namespace Sequence {
	namespace Game {
		Parent::Parent():
			mChildPtr(new Ready()),
			mStageId(-1)
		{}
		Base* Parent::update(std::shared_ptr<Sequence::Parent> parent) {
			if (mStageId == -1) {
				if (parent->getGameMode() == Sequence::Parent::GameMode::MODE_SOLO) {
					mStageId = 1;
				}
				else {
					mStageId = 0;
				}
			}

			Base* next = mChildPtr->update(this);
			if (mChildPtr.get() != next) {
				mChildPtr.reset(next);
			}
			return mChildPtr.get();


			return mSeq = next;
		}
	}
}