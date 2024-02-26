#ifndef SEQUENCE_PARENT_H
#define SEQUENCE_PARENT_H

#include "Sequence/Title.h"
#include "Sequence/GameOver.h"
#include "Sequence/Ending.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Base.h"
#include <memory>

namespace Sequence{
	class Parent: public Base
	{
	public:
		Parent();
		Base* update(std::shared_ptr<Base> parent);
		enum class GameMode {
			MODE_SOLO,
			MODE_DUO,
		};
		void setGameMode(GameMode game_mode);
		GameMode getGameMode()const;

	private:
		std::shared_ptr<Base> mChildPtr;
		GameMode mGameMode;
	};

}
#endif // SEQUENCE_PARENT_H

