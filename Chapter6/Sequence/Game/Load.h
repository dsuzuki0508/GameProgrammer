#ifndef SEQUENCEC_GAME_LOAD_H
#define SEQUENCEC_GAME_LOAD_H
#include <memory>
#include "Image.h"
#include "State.h"
namespace Sequence {
	namespace Game {
		class Load
		{
		public:
			enum class SeqId {
				SEQ_LOAD,
				SEQ_END,
			};
			Load(std::unique_ptr<State>& state_ptr, unsigned stage_id);
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

#endif // SEQUENCEC_GAME_LOAD_H