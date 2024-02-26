#ifndef SEQUENCE_BASE_H
#define SEQUENCE_BASE_H

namespace Sequence {
	class Base {
		virtual Base* update(Base* const parent) = 0;
	};
}
#endif // SEQUENCE_BASE_H