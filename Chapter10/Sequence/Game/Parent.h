#ifndef SEQUENCE_GAME_PARENT_H
#define SEQUENCE_GAME_PARENT_H

#include "Sequence/Game/Ready.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Failure.h"
#include "Sequence/Game/Result.h"
#include "Sequence/Child.h"
#include "Sequence/Game/Child.h"

#include <memory>



namespace Sequence {
	namespace Game {
		class Parent:public Sequence::Child
		{
		public:
			Parent();
			Base* update(std::shared_ptr<Sequence::Parent> parent);
		private:
			std::shared_ptr<Game::Child> mChildPtr;
			unsigned mStageId;
		};
	}

}

#endif // SEQUENCE_GAME_PARENT_H

