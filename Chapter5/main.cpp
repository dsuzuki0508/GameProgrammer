#include "GameLib/Framework.h"
#include "Move.h"
#include "State.h"
#include "Image.h"
#include "Sequence.h"
#include "Defines.h"
#include "Sequence/Parent.h"

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<math.h>
#include <assert.h>
using namespace std;


namespace GameLib {
	void Framework::update() {
		static unique_ptr<Sequence::Parent> rootSequence(new Sequence::Parent());

		setFrameRate(MAX_FRAME_RATE);

		static unsigned count = 0;
		if (++count % 60 == 0)GameLib::cout << "FrameRate: " << frameRate() << GameLib::endl;

		rootSequence->update();

		if ( isKeyOn('q')) {
			requestEnd();
		}
		if (isEndRequested()) {
			return;
		}
	}
}

