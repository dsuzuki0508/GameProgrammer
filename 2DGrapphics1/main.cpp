#include "GameLib/Framework.h"
#include "Move.h"
#include "State.h"
#include "Image.h"

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<math.h>
#include <assert.h>
using namespace std;

Move getInput() {
	char c;
	GameLib::cout << "a:left s:right w:up z:down. command?" << GameLib::endl;
	GameLib::cin >> c;

	return Move(c);
}

void mainLoop() {
	static unique_ptr<Image> image_ptr;
	if (!image_ptr) {
		image_ptr.reset(new Image("image2.dds"));
	}

	static unique_ptr<State> state_ptr;
	if (!state_ptr) {

		ifstream ifs("stageData.txt", ifstream::binary);
		ifs.seekg(0, ifstream::end);
		int file_size = static_cast<int>(ifs.tellg());
		ifs.seekg(0, ifstream::beg);
		unique_ptr<char[]> buff(new char[file_size]);
		ifs.read(buff.get(), file_size);

		state_ptr.reset(new State(buff.get(), file_size));

		state_ptr->draw(image_ptr);

		return;
	}
	
	auto move = getInput();
	state_ptr->update(move);
	state_ptr->draw(image_ptr);
	if (state_ptr->isClearedState()) {
		GameLib::cout << "Congratulation! you win." << GameLib::endl;
		state_ptr.reset();
		GameLib::Framework::instance().requestEnd();
		return;
	}
	if (move.hasEndRequested()) {
		GameLib::Framework::instance().requestEnd();
		return;
	}
	if (GameLib::Framework::instance().isEndRequested()) {
		return;
	}
}

namespace GameLib {
	void Framework::update() {
		mainLoop();
	}
}

