#ifndef SEQUENCE_GAME_PARENT_H
#define SEQUENCE_GAME_PARENT_H

#include "Sequence/Game/Ready.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Failure.h"
#include "Sequence/Game/Result.h"

#include <memory>



namespace Sequence {
	namespace Game {
		class Parent
		{
		public:
			enum class SeqId {
				SEQ_READY,
				SEQ_PLAY,
				SEQ_MENU,
				SEQ_CLEAR,
				SEQ_FAILURE,
				SEQ_RESULT,
				SEQ_TO_TITLE,
				SEQ_TO_GAME_OVER,
				SEQ_TO_ENDING,
			};
			Parent(unsigned stage_id);
			SeqId update();
		private:
			SeqId mSeq;
			std::unique_ptr<Ready> mReadyPtr;
			std::unique_ptr<Play> mPlayPtr;
			std::unique_ptr<Menu> mMenuPtr;
			std::unique_ptr<Clear> mClearPtr;
			std::unique_ptr<State> mStatePtr;
			std::unique_ptr<Failure> mFailurePtr;
			std::unique_ptr<Result> mResultPtr;
			unsigned mStageId;
		};
	}

}

#endif // SEQUENCE_GAME_PARENT_H

