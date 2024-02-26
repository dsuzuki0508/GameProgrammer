#include "Sequence/Game/Menu.h"
#include "Image.h"
#include "GameLib/Framework.h"
#include <assert.h>
using namespace std;

namespace Sequence {
	namespace Game {
		Menu::Menu(unique_ptr<State>& state_ptr) :
			mStatePtr(state_ptr),
			mSeq(SeqId::SEQ_MENU),
			mMenuImagePtr(new MenuImage("menu.dds")),
			mCellsImagePtr(new CellsImage("image2.dds"))
		{}
		Menu::SeqId Menu::update() {
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_MENU:
				assert(mStatePtr);
				if (GameLib::Framework::instance().isKeyTriggered('1')) {
					next = SeqId::SEQ_TO_LOAD;
				}
				else if (GameLib::Framework::instance().isKeyTriggered('2')) {
					next = SeqId::SEQ_TO_STAGE_SELECT;
				}
				else if (GameLib::Framework::instance().isKeyTriggered('3')) {
					next = SeqId::SEQ_TO_TITLE;
				}
				else if (GameLib::Framework::instance().isKeyTriggered('4')) {
					next = SeqId::SEQ_END;
				}
				mStatePtr->draw(mCellsImagePtr);
				mMenuImagePtr->drawImage(0, 0, MenuImage::Id::IMG_MENU);
			default:
				break;
			}

			return mSeq = next;
		}
	}
}