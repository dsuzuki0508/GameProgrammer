#ifndef SEQUENCEC_TITLE_H
#define SEQUENCEC_TITLE_H
#include <memory>
#include "Image.h"
namespace Sequence {
	class Title
	{
	public:
		enum class SeqId {
			SEQ_TITLE,
			SEQ_TO_GAME_SOLO,
			SEQ_TO_GAME_DUO
		};
		Title();
		SeqId update();
	private:
		SeqId mSeq;
		std::unique_ptr<TitleImage> mTitleImagePtr;
		unsigned mSelectedMode;
	};
}

#endif // SEQUENCEC_TITLE_H