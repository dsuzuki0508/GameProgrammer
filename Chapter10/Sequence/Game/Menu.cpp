#include "Sequence/Game/Menu.h"
#include "Image.h"
#include "GameLib/Framework.h"
#include "Pad.h"
#include <assert.h>
using namespace std;

namespace Sequence {
	namespace Game {
		int getInput() {
			if (Pad::isTriggered(Pad::Button::U)) {
				return -1;
			}
			else if (Pad::isTriggered(Pad::Button::D)) {
				return 1;
			}
			return 0;
		}
		Menu::Menu(unique_ptr<State>& state_ptr) :
			mStatePtr(state_ptr),
			mSeq(SeqId::SEQ_MENU),
			mMenuImagePtr(new MenuImage("data/image/menu.dds"))
		{}
		Menu::SeqId Menu::update() {
			SeqId next = mSeq;
			switch (mSeq) {
			case SeqId::SEQ_MENU:
				assert(mStatePtr);
				mSelectedRow = (mSelectedRow + getInput()+2) % 2;
				if (Pad::isTriggered(Pad::Button::A)) {
					switch (mSelectedRow) {
					case 0:
						next = SeqId::SEQ_TO_TITLE;
						break;
					case 1:
						next = SeqId::SEQ_END;
						break;
					default:
						break;
					}
				}
				else if (Pad::isTriggered(Pad::Button::B)) {
					next = SeqId::SEQ_END;
				}
				mStatePtr->draw();
				mMenuImagePtr->drawImage(0, 0, MenuImage::Id::IMG_MENU);
				{
					FontImage& font = FontImage::instance();
					font.drawString(0, 0, "[MENU]");
					font.drawString(1, 1, "GO TO TITLE", true, mSelectedRow == 0 ? 0xffffffff : 0x777777);
					font.drawString(2, 1, "CONTINUE", true, mSelectedRow == 1 ? 0xffffffff : 0x777777);
//  				font.drawString(mSelectedRow + 1, 0, ">", true, 0xff0000);
				}

			default:
				break;
			}

			return mSeq = next;
		}
	}
}