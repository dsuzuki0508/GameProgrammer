#ifndef SEQUENCEC_GAME_FAILURE_H
#define SEQUENCEC_GAME_FAILURE_H
#include <memory>
#include "Image.h"
#include "Game/State.h"
namespace Sequence {
	namespace Game {
		class Failure
		{
		public:
			enum class SeqId {
				SEQ_FAILURE,
				SEQ_END,
			};
			Failure(std::unique_ptr<State>& state_ptr);
			SeqId update();
		private:
			SeqId mSeq;
			unsigned mCountMSec;
			std::unique_ptr<State>& mStatePtr;
		};
	}
}

#endif // SEQUENCEC_GAME_CLEAR_H