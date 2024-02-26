#ifndef SEQUENCE_CHILD_H
#define SEQUENCE_CHILD_H
#include "Sequence/Base.h"
#include "Sequence/Parent.h"
#include <assert.h>
namespace Sequence {
	class Child : public Base {
		Base* update(Base* const p);
		virtual Base* update(Parent* const parent) = 0;
	};
}

#endif SEQUENCE_CHILD_H