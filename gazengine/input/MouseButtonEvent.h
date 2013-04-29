#ifndef MOUSEBUTTONEVENT_H_
#define MOUSEBUTTONEVENT_H_

#include "Button.h"
#include "Mouse.h"

struct MouseButtonEvent
{
	MouseButtonEvent() :
		button(Mouse::UNKNOWN_BUTTON), buttonState(Button::UNKNOWN_STATE), x(0), y(0)
	{
	}

	/**
	 * The button that triggered the event.
	 */
	Mouse::Button button;

	/**
	 * The new state of the button.
	 */
	Button::State buttonState;

	/**
	 * The location at which the event took place on the x axis.
	 */
	int x;

	/**
	 * The location at which the event took place on the y axis.
	 */
	int y;
};

#endif /* MOUSEBUTTONEVENT_H_ */
