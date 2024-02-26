#include "Sequence/Child.h"
namespace Sequence {
	Base* Child::update(Base* const p) {
		Parent* const parent = dynamic_cast<Parent*>(p);
		assert(parent);
		return update(parent);
	}
}