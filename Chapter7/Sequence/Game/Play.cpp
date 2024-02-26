#include "Sequence/Game/Play.h"
#include "Image.h"
#include "GameLib/Framework.h"
#include "Game/Move.h"
#include <assert.h>
using namespace std;

namespace Sequence {
	namespace Game {

		Move getInput() {
			static Move old;
			//    GameLib::cout << "a:left s:right w:up z:down. command?" << GameLib::endl;
				//GameLib::cout << "I" << GameLib::endl<<"II"<<GameLib::endl;
			Move next;
			if (GameLib::Framework::instance().isKeyTriggered(' '))next = Move(' '); 
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
			mCellsImagePtr(new CellsImage("data/image/image2.dds"))
		{}
		Play::SeqId Play::update() {
#ifndef NDEBUG
			if (GameLib::Framework::instance().isKeyTriggered('1')) {
				mStatePtr->mWinner = 1;
				return mSeq = SeqId::SEQ_TO_RESULT;
			}
			else if (GameLib::Framework::instance().isKeyTriggered('2')) {
				mStatePtr->mWinner = 2;
				return mSeq = SeqId::SEQ_TO_RESULT;
			}
			else if (GameLib::Framework::instance().isKeyTriggered('c')) {
				return mSeq = SeqId::SEQ_TO_CLEAR;
			}
			else if (GameLib::Framework::instance().isKeyTriggered('f')) {
				return mSeq = SeqId::SEQ_TO_FAILURE;
			}
#endif
			SeqId next = mSeq;
			Move move;
			switch (mSeq) {
			case SeqId::SEQ_PLAY:
				assert(mStatePtr);
				assert(mCellsImagePtr);
				move = getInput();
				mStatePtr->update(move);
				mStatePtr->draw();
				if (mStatePtr->hasCleared()) {
					GameLib::cout << "Congratulation! you win." << GameLib::endl;
					//GameLib::Framework::instance().requestEnd();
					next= SeqId::SEQ_TO_CLEAR;
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