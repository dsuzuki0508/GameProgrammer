#ifndef SEQUENCEC_GAMEOVER_H
#define SEQUENCEC_GAMEOVER_H
#include <memory>
namespace Sequence {
	class GameOver
	{
	public:
		enum class SeqId {
			SEQ_GAMEOVER,
			SEQ_END,
		};
		GameOver();
		SeqId update();
	private:
		SeqId mSeq;
		unsigned mCountMSec;
	};
}

#endif // SEQUENCEC_GAMEOVER_H