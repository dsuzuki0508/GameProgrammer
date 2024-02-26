#ifndef SEQUENCEC_GAMEOVER_H
#define SEQUENCEC_GAMEOVER_H
#include <memory>
#include "Sequence/Child.h"
namespace Sequence {
	class GameOver: public Child
	{
	public:
		GameOver();
		Base* update(std::shared_ptr<Parent> parent);
	private:
		unsigned mCountMSec;
	};
}

#endif // SEQUENCEC_GAMEOVER_H