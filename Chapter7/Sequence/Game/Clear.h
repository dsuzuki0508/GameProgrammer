#ifndef SEQUENCEC_GAME_CLEAR_H
#define SEQUENCEC_GAME_CLEAR_H
#include <memory>
#include "Image.h"
#include "Game/State.h"
namespace Sequence {
	namespace Game {
		class Clear
		{
		public:
			enum class SeqId {
				SEQ_CLEAR,
				SEQ_END,
			};
			Clear(std::unique_ptr<State>& state_ptr);
			SeqId update();
		private:
			SeqId mSeq;
			std::unique_ptr<ClearImage> mClearImagePtr;
			unsigned mCountMSec;
			std::unique_ptr<State>& mStatePtr;
		};
	}
}

#endif // SEQUENCEC_GAME_CLEAR_H