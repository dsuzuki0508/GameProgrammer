#include "Sequence/Game/Menu.h"
#include "Image.h"
#include "GameLib/Framework.h"
#include <assert.h>
using namespace std;

namespace Sequence {
	namespace Game {
		int getInput() {
			if (GameLib::Framework::instance().isKeyTriggered('w')) {
				return -1;
			}
			else if (GameLib::Framework::instance().isKeyTriggered('z')) {
				return 1;
			}
			return 0;
		}
		Menu::Menu(unique_ptr<State>& state_ptr) :
			mStatePtr(state_ptr),
			mSeq(SeqId::SEQ_MENU),
			mMenuImagePtr(new MenuImage("data/image/menu.dds")),
			mCellsImagePtr(new CellsImage("data/image/image2.dds"))
		{}
		Menu::SeqId Menu::update() {
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_MENU:
				assert(mStatePtr);
				mSelectedRow = (mSelectedRow + getInput()+4) % 4;
				if (GameLib::Framework::instance().isKeyTriggered(' ')) {
					switch (mSelectedRow) {
					case 0:
						next = SeqId::SEQ_TO_LOAD;
						break;
					case 1:
						next = SeqId::SEQ_TO_STAGE_SELECT;
						break;
					case 2:
						next = SeqId::SEQ_TO_TITLE;
						break;
					case 3:
						next = SeqId::SEQ_END;
						break;
					default:
						break;
					}
				}
				mStatePtr->draw(mCellsImagePtr);
				mMenuImagePtr->drawImage(0, 0, MenuImage::Id::IMG_MENU);
				{
					FontImage& font = FontImage::instance();
					font.drawString(0, 0, "[MENU]");
					font.drawString(1, 1, "RETRY", true, mSelectedRow == 0 ? 0xffffff : 0x777777);
					font.drawString(2, 1, "GO TO STAGE SELECT", true, mSelectedRow == 1 ? 0xffffff : 0x777777);
					font.drawString(3, 1, "GO TO TITLE", true, mSelectedRow == 2 ? 0xffffff : 0x777777);
					font.drawString(4, 1, "CONTINUE", true, mSelectedRow == 3 ? 0xffffff : 0x777777);
//  				font.drawString(mSelectedRow + 1, 0, ">", true, 0xff0000);
				}

			default:
				break;
			}

			return mSeq = next;
		}
	}
}