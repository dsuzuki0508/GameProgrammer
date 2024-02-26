#include "Sequence/Ending.h"
#include "GameLib/Framework.h"
#include "Sequence/Title.h"
#include <algorithm>
using namespace std;
namespace Sequence {
	Ending::Ending():
		mCountMSec(3000)
	{}
	Base* Ending::update(Parent* const parent) {
		Base* next = this;
		static GameLib::Framework f = GameLib::Framework::instance();

		mCountMSec -= min(mCountMSec, static_cast<unsigned>(f.previousFrameInterval()));
		if (mCountMSec == 0) {
			next = new Sequence::Title();
		}
		f.drawDebugString(1, 1, "ENDING");
		return next;
	}
}