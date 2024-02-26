#include "Sequence/Parent.h"
#include "Sequence/Title.h"
#include "Sequence/GameOver.h"
#include "Sequence/Ending.h"
#include "Sequence/Game/Parent.h"

using namespace std;

namespace Sequence {
	Parent::Parent() :
		mChildPtr(new Title()),
		mGameMode(GameMode::MODE_SOLO)
	{}
	Base* Parent::update(std::shared_ptr<Base> parent) {
		Base* next = mChildPtr->update(this);
		if (mChildPtr.get() != next) {
			mChildPtr.reset(next);
		}
		return mChildPtr.get();
	}
	void Parent::setGameMode(GameMode game_mode)
	{
		mGameMode = game_mode;
	}
	Parent::GameMode Parent::getGameMode()const
	{
		return mGameMode;
	}
}