#ifndef KEYBOARDBUTTONEVENT_H_
#define KEYBOARDBUTTONEVENT_H_

#include "Button.h"
#include "Keyboard.h"

struct KeyboardButtonEvent
{
	KeyboardButtonEvent() :
		button(Keyboard::UNKNOWN_BUTTON), buttonState(Button::UNKNOWN_STATE), character(0)
	{
	}

	/**
	 * The button that triggered the event.
	 */
	Keyboard::Button button;

	/**
	 * The new state of the button.
	 */
	Button::State buttonState;

	/**
	 * The key that triggered the event.
	 */
	unsigned char character;
};

#endif /* KEYBOARDBUTTONEVENT_H_ */
