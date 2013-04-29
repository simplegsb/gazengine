#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <map>

namespace Keyboard
{
	enum Button
	{
		ZERO,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,

		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,

		APOSTROPHE,
		ARROW_DOWN,
		ARROW_LEFT,
		ARROW_RIGHT,
		ARROW_UP,
		ASTERISK,
		AT,
		BACKSLASH,
		BACKSPACE,
		COLON,
		COMMA,
		DEL,
		END,
		ESCAPE,
		EQUALS,
		GRAVE,
		HOME,
		INSERT,
		LEFT_ALT,
		LEFT_BRACKET,
		LEFT_CTRL,
		LEFT_SHIFT,
		MINUS,
		PAGE_DOWN,
		PAGE_UP,
		PERIOD,
		RETURN,
		RIGHT_ALT,
		RIGHT_BRACKET,
		RIGHT_CTRL,
		RIGHT_SHIFT,
		SEMICOLON,
		SLASH,
		SPACE,
		TAB,
		UNDERLINE,

		UNKNOWN_BUTTON
	};
}

std::map<unsigned char, Keyboard::Button> createAsciiKeyboardButtonMap();

#endif /* KEYBOARD_H_ */
