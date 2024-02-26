#ifndef SEQUENCEC_ENDING_H
#define SEQUENCEC_ENDING_H
#include <memory>
namespace Sequence {
	class Ending
	{
	public:
		enum class SeqId {
			SEQ_ENDING,
			SEQ_END,
		};
		Ending();
		SeqId update();
	private:
		SeqId mSeq;
		unsigned mCountMSec;
	};
}

#endif // SEQUENCEC_ENDING_H