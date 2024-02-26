#ifndef SEQUENCEC_ENDING_H
#define SEQUENCEC_ENDING_H
#include "Sequence/Child.h"
#include <memory>
namespace Sequence {
	class Ending:public Child
	{
	public:
		Ending();
		Base* update(Parent* const parent);
	private:
		unsigned mCountMSec;
	};
}

#endif // SEQUENCEC_ENDING_H