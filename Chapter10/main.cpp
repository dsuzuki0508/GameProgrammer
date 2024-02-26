#include "GameLib/Framework.h"
#include "Game/State.h"
#include "Image.h"
#include "Defines.h"
#include "Sequence/Parent.h"
#include "Pad.h"

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<math.h>
#include <assert.h>
#include <sstream>
#include<iomanip>
using namespace std;


namespace GameLib {
	void Framework::update() {
		setFrameRate(MAX_FRAME_RATE);
		static unique_ptr<Sequence::Parent> rootSequence(new Sequence::Parent());
		rootSequence->update();
		stringstream ss;
		ss << "FrameRate:" << right << setw(4) << frameRate();
		instance().drawDebugString(80 - ss.str().size(), 0, ss.str().c_str(), 0xffffffff);
//		GameLib::cout << "FrameRate: " << frameRate() << GameLib::endl;

		if (Pad::isOn(Pad::Button::Q)) {
			requestEnd();
		}
		if (isEndRequested()) {
			return;
		}
	}
}

