#ifndef SEQUENCEC_GAME_RESULT_H
#define SEQUENCEC_GAME_RESULT_H
#include <memory>
#include "Image.h"
#include "Game/State.h"
namespace Sequence {
	namespace Game {
		class Result
		{
		public:
			enum class SeqId {
				SEQ_RESULT,
				SEQ_END,
			};
			Result(std::unique_ptr<State>& state_ptr);
			SeqId update();
		private:
			SeqId mSeq;
			unsigned mCountMSec;
			std::unique_ptr<State>& mStatePtr;
			std::unique_ptr<CellsImage> mCellsImagePtr;
		};
	}
}

#endif // SEQUENCEC_GAME_RESULT_H