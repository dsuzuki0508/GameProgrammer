#include "Sequence/Game/Play.h"
#include "Image.h"
#include "GameLib/Framework.h"
#include "Move.h"
#include <assert.h>
using namespace std;

namespace Sequence {
	namespace Game {

		Move getInput() {
			static Move old;
			//    GameLib::cout << "a:left s:right w:up z:down. command?" << GameLib::endl;
				//GameLib::cout << "I" << GameLib::endl<<"II"<<GameLib::endl;
			Move next;
			if (GameLib::Framework::instance().isKeyOn(' '))next = Move(' '); 
			else if (GameLib::Framework::instance().isKeyOn('a'))next = Move('a'); 
			else if (GameLib::Framework::instance().isKeyOn('s'))next = Move('s'); 
			else if (GameLib::Framework::instance().isKeyOn('w'))next = Move('w'); 
			else if (GameLib::Framework::instance().isKeyOn('z'))next = Move('z');

			return next;
			if (old != next)return old = next;
			else return Move(0);
		}

		Play::Play(unique_ptr<State>& state_ptr) :
			mStatePtr(state_ptr),
			mSeq(SeqId::SEQ_PLAY),
			mCellsImagePtr(new CellsImage("image2.dds"))
		{}
		Play::SeqId Play::update() {
			SeqId next = mSeq;
			Move move;
			switch (mSeq) {
			case SeqId::SEQ_PLAY:
				assert(mStatePtr);
				assert(mCellsImagePtr);
				move = getInput();
				mStatePtr->update(move);
				mStatePtr->draw(mCellsImagePtr);
				if (mStatePtr->isClearedState()) {
					GameLib::cout << "Congratulation! you win." << GameLib::endl;
					//GameLib::Framework::instance().requestEnd();
					next= SeqId::SEQ_END;
				}else if (move.hasMenuRequested()) {
					return SeqId::SEQ_TO_MENU;
				}
				else {
					next = SeqId::SEQ_PLAY;
				}
				break;
			default:
				break;
			}

			return mSeq = next;
		}
	}
}