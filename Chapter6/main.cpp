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
#include <sstream>
#include<iomanip>
using namespace std;


namespace GameLib {
	void Framework::update() {
		static unique_ptr<Sequence::Parent> rootSequence(new Sequence::Parent());

		setFrameRate(MAX_FRAME_RATE);


		rootSequence->update();

		stringstream ss;
		ss << "FrameRate:" << right << setw(4) << frameRate();
		FontImage::instance().drawString(0, 40 - ss.str().size(), ss.str(), true, 0xbbbbbb);
//		GameLib::cout << "FrameRate: " << frameRate() << GameLib::endl;

		if ( isKeyOn('q')) {
			requestEnd();
		}
		if (isEndRequested()) {
			return;
		}
	}
}

