#ifndef SEQUENCEC_GAME_PLAY_H
#define SEQUENCEC_GAME_PLAY_H
#include <memory>
#include "Image.h"
#include "State.h"
namespace Sequence {
	namespace Game {
		class Play
		{
		public:
			enum class SeqId {
				SEQ_PLAY,
				SEQ_TO_MENU,
				SEQ_END,
			};
			Play(std::unique_ptr<State>& state_ptr);
			SeqId update();
		private:
			SeqId mSeq;
			std::unique_ptr<CellsImage> mCellsImagePtr;
			std::unique_ptr<State>& mStatePtr;
		};
	}
}

#endif // SEQUENCEC_GAME_LOAD_H