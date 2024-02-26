#ifndef SEQUENCEC_GAME_MENU_H
#define SEQUENCEC_GAME_MENU_H
#include <memory>
#include "Image.h"
#include "State.h"
namespace Sequence {
	namespace Game {
		class Menu
		{
		public:
			enum class SeqId {
				SEQ_MENU,
				SEQ_TO_LOAD,
				SEQ_TO_STAGE_SELECT,
				SEQ_TO_TITLE,
				SEQ_END,
			};
			Menu(std::unique_ptr<State>& state_ptr);
			SeqId update();
		private:
			SeqId mSeq;
			std::unique_ptr<MenuImage> mMenuImagePtr;
			std::unique_ptr<CellsImage> mCellsImagePtr;
			std::unique_ptr<State>& mStatePtr;
			unsigned mSelectedRow = 0;
		};
	}
}

#endif // SEQUENCEC_GAME_LOAD_H