#ifndef SEQUENCE_PARENT_H
#define SEQUENCE_PARENT_H

#include "Sequence/Title.h"
#include "Sequence/StageSelect.h"
#include "Sequence/Game/Parent.h"
#include <memory>



namespace Sequence{
	class Parent
	{
	public:
		enum class SeqId {
			SEQ_TITLE,
			SEQ_GAME,
			SEQ_STAGE_SELECT,
		};
		Parent();
		SeqId update();
	private:
		SeqId mSeq;
		std::unique_ptr<Title> mTitlePtr;
		std::unique_ptr<StageSelect> mStageSelectPtr;
		std::unique_ptr<Game::Parent> mGamePtr;
		unsigned mStage;
	};

}
#endif // SEQUENCE_PARENT_H

