#include "FreeGLUTKeyboard.h"

using namespace std;

map<int, Keyboard::Button> createSpecialKeyoardButtonMap()
{
	map<int, Keyboard::Button> specialButtonMap;

	specialButtonMap.insert(pair<int, Keyboard::Button>(1, Keyboard::F1));
	specialButtonMap.insert(pair<int, Keyboard::Button>(2, Keyboard::F2));
	specialButtonMap.insert(pair<int, Keyboard::Button>(3, Keyboard::F3));
	specialButtonMap.insert(pair<int, Keyboard::Button>(4, Keyboard::F4));
	specialButtonMap.insert(pair<int, Keyboard::Button>(5, Keyboard::F5));
	specialButtonMap.insert(pair<int, Keyboard::Button>(6, Keyboard::F6));
	specialButtonMap.insert(pair<int, Keyboard::Button>(7, Keyboard::F7));
	specialButtonMap.insert(pair<int, Keyboard::Button>(8, Keyboard::F8));
	specialButtonMap.insert(pair<int, Keyboard::Button>(9, Keyboard::F9));
	specialButtonMap.insert(pair<int, Keyboard::Button>(10, Keyboard::F10));
	specialButtonMap.insert(pair<int, Keyboard::Button>(11, Keyboard::F11));
	specialButtonMap.insert(pair<int, Keyboard::Button>(12, Keyboard::F12));

	specialButtonMap.insert(pair<int, Keyboard::Button>(103, Keyboard::ARROW_DOWN));
	specialButtonMap.insert(pair<int, Keyboard::Button>(100, Keyboard::ARROW_LEFT));
	specialButtonMap.insert(pair<int, Keyboard::Button>(102, Keyboard::ARROW_RIGHT));
	specialButtonMap.insert(pair<int, Keyboard::Button>(101, Keyboard::ARROW_UP));
	specialButtonMap.insert(pair<int, Keyboard::Button>(107, Keyboard::END));
	specialButtonMap.insert(pair<int, Keyboard::Button>(106, Keyboard::HOME));
	specialButtonMap.insert(pair<int, Keyboard::Button>(108, Keyboard::INSERT));
	specialButtonMap.insert(pair<int, Keyboard::Button>(105, Keyboard::PAGE_DOWN));
	specialButtonMap.insert(pair<int, Keyboard::Button>(104, Keyboard::PAGE_UP));

	return specialButtonMap;
}
