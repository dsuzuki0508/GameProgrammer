#ifndef SEQUENCEC_GAME_READY_H
#define SEQUENCEC_GAME_READY_H
#include <memory>
#include "Image.h"
#include "Game/State.h"
namespace Sequence {
	namespace Game {
		class Ready
		{
		public:
			enum class SeqId {
				SEQ_READY,
				SEQ_END,
			};
			Ready(std::unique_ptr<State>& state_ptr, unsigned stage_id);
			SeqId update();
		private:
			SeqId mSeq;
			std::unique_ptr<LoadingImage> mLoadingImagePtr;
			unsigned mCountMSec;
			std::unique_ptr<State>& mStatePtr;
			unsigned mStageId;
		};
	}
}

#endif // SEQUENCEC_GAME_READY_H