#ifndef SEQUENCEC_STAGE_SELECT_H
#define SEQUENCEC_STAGE_SELECT_H
#include <memory>
#include "Image.h"
namespace Sequence {
	class StageSelect
	{
	public:
		enum class SeqId {
			SEQ_STAGE_SELECT,
			SEQ_END,
		};
		StageSelect();
		SeqId update(unsigned& stage_id);
	private:
		SeqId mSeq;
		std::unique_ptr<StageSelectImage> mStageSelectImagePtr;
	};
}

#endif // SEQUENCEC_STAGE_SELECT_H