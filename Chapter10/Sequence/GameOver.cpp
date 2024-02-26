#include "Sequence/GameOver.h"
#include "GameLib/Framework.h"
#include <algorithm>
using namespace std;
namespace Sequence {
	GameOver::GameOver():
		mCountMSec(3000)
	{}
	Base* GameOver::update(std::shared_ptr<Parent> parent)
	{
		Base* next = this;
		static GameLib::Framework f = GameLib::Framework::instance();
		mCountMSec -= min(mCountMSec, static_cast<unsigned>(f.previousFrameInterval()));
		if (mCountMSec == 0) {
			next = new Title();
		}
		f.drawDebugString(1, 1, "GAME OVER");

		return next;
	}
}