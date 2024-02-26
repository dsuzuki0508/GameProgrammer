#ifndef SEQUENCE_PARENT_H
#define SEQUENCE_PARENT_H

#include "Sequence/Title.h"
#include "Sequence/GameOver.h"
#include "Sequence/Ending.h"
#include "Sequence/Game/Parent.h"
#include <memory>

namespace Sequence{
	class Parent
	{
	public:
		enum class SeqId {
			SEQ_TITLE,
			SEQ_GAME_SOLO,
			SEQ_GAME_DUO,
			SEQ_GAME_OVER,
			SEQ_ENDING,
		};
		Parent();
		SeqId update();
	private:
		SeqId mSeq;
		std::unique_ptr<Title> mTitlePtr;
		std::unique_ptr<Game::Parent> mGamePtr;
		std::unique_ptr<GameOver> mGameOverPtr;
		std::unique_ptr<Ending> mEndingPtr;
	};

}
#endif // SEQUENCE_PARENT_H

