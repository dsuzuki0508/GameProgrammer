#include "Pad.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include <map>
using namespace std;
bool Pad::isOn(Button b, int playerId)
{
	if (playerId) {
		static map<Button, char> mp = {
			{Button::A, 'l'},
			{Button::B,'.'},
			{Button::U,'i'},
			{Button::D,'m'},
			{Button::L,'j'},
			{Button::R,'k'},
			{Button::Q,'q'}, };
		return GameLib::Input::Manager::instance().keyboard().isOn(mp[b]);
	}
	else {
		static map<Button, char> mp = {
			{Button::A, 'd'},
			{Button::B,'x'},
			{Button::U,'w'},
			{Button::D,'z'},
			{Button::L,'a'},
			{Button::R,'s'},
			{Button::Q,'q'}, };
		return GameLib::Input::Manager::instance().keyboard().isOn(mp[b]);
	}
}

bool Pad::isTriggered(Button b, int playerId)
{
	if (playerId) {
		static map<Button, char> mp = {
			{Button::A, 'l'},
			{Button::B,'.'},
			{Button::U,'i'},
			{Button::D,'m'},
			{Button::L,'j'},
			{Button::R,'k'},
			{Button::Q,'q'}, };
		return GameLib::Input::Manager::instance().keyboard().isTriggered(mp[b]);
	}
	else {
		static map<Button, char> mp = {
			{Button::A, 'd'},
			{Button::B,'x'},
			{Button::U,'w'},
			{Button::D,'z'},
			{Button::L,'a'},
			{Button::R,'s'},
			{Button::Q,'q'}, };
		return GameLib::Input::Manager::instance().keyboard().isTriggered(mp[b]);
	}
}
