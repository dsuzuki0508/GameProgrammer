#ifndef SEQUENCE_GAME_CHILD_H
#define SEQUENCE_GAME_CHILD_H
#include "Sequence/Base.h"
#include "Sequence/Parent.h"
#include <memory>
#include <assert.h>
namespace Sequence {
	namespace Game {
		class Child : public Base {
			Base* update(std::shared_ptr<Base> p);
			virtual Base* update(std::shared_ptr<Parent> parent) = 0;
		};
	}
}
#endif // SEQUENCE_GAME_CHILD_H