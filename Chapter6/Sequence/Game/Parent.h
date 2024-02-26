#ifndef SEQUENCE_GAME_PARENT_H
#define SEQUENCE_GAME_PARENT_H

#include "Sequence/Game/Load.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Clear.h"

#include <memory>



namespace Sequence {
	namespace Game {
		class Parent
		{
		public:
			enum class SeqId {
				SEQ_LOAD,
				SEQ_PLAY,
				SEQ_MENU,
				SEQ_CLEAR,
				SEQ_TO_TITLE,
				SEQ_TO_STAGE_SELECT,
				SEQ_END,
			};
			Parent(unsigned stage);
			SeqId update();
		private:
			SeqId mSeq = SeqId::SEQ_LOAD;
			std::unique_ptr<Load> mLoadPtr;
			std::unique_ptr<Play> mPlayPtr;
			std::unique_ptr<Menu> mMenuPtr;
			std::unique_ptr<Clear> mClearPtr;
			std::unique_ptr<State> mStatePtr;
			unsigned mStage;
		};
	}

}

#endif // SEQUENCE_GAME_PARENT_H

