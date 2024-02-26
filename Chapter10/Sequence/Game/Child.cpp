#include "Sequence/Game/Child.h"
namespace Sequence {
	namespace Game {
		Base* Child::update(std::shared_ptr<Base> p) {
			std::shared_ptr<Parent> parent = std::dynamic_pointer_cast<Parent>(p);
			assert(parent);
			return update(parent);
		}
	}
}