#include <GL/freeglut.h>

#include <gazengine/Events.h>
#include <gazengine/Messages.h>

#include "FreeGLUTInputEvents.h"
#include "FreeGLUTKeyboard.h"

using namespace std;

bool altActive = false;

bool ctrlActive = false;

map<unsigned char, Keyboard::Button> freeGlutAsciiKeyboardButtonMap = createAsciiKeyboardButtonMap();

map<int, Keyboard::Button> freeGlutSpecialKeyboardButtonMap = createSpecialKeyoardButtonMap();

bool shiftActive = false;

void fireKeyboardButtonDownEvent(const unsigned char key, const int x, const int y)
{
	KeyboardButtonEvent event = getKeyboardButtonEvent(key);
	event.buttonState = Button::DOWN;

	fireKeyboardModifierButtonEvent();
	Messages::send(Events::KEYBOARD_BUTTON, &event);
}

void fireKeyboardButtonUpEvent(const unsigned char key, const int x, const int y)
{
	KeyboardButtonEvent event = getKeyboardButtonEvent(key);
	event.buttonState = Button::UP;

	fireKeyboardModifierButtonEvent();
	Messages::send(Events::KEYBOARD_BUTTON, &event);
}

void fireKeyboardModifierButtonEvent()
{
	int activeModifiers = glutGetModifiers();

	if (activeModifiers & GLUT_ACTIVE_ALT)
	{
		if (!altActive)
		{
			altActive = true;

			KeyboardButtonEvent event;
			event.button = Keyboard::LEFT_ALT;
			event.buttonState = Button::DOWN;

			Messages::send(Events::KEYBOARD_BUTTON, &event);
		}
	}
	else
	{
		if (altActive)
		{
			altActive = false;

			KeyboardButtonEvent event;
			event.button = Keyboard::LEFT_ALT;
			event.buttonState = Button::UP;

			Messages::send(Events::KEYBOARD_BUTTON, &event);
		}
	}

	if (activeModifiers & GLUT_ACTIVE_CTRL)
	{
		if (!ctrlActive)
		{
			ctrlActive = true;

			KeyboardButtonEvent event;
			event.button = Keyboard::LEFT_CTRL;
			event.buttonState = Button::DOWN;

			Messages::send(Events::KEYBOARD_BUTTON, &event);
		}
	}
	else
	{
		if (ctrlActive)
		{
			ctrlActive = false;

			KeyboardButtonEvent event;
			event.button = Keyboard::LEFT_CTRL;
			event.buttonState = Button::UP;

			Messages::send(Events::KEYBOARD_BUTTON, &event);
		}
	}

	if (activeModifiers & GLUT_ACTIVE_SHIFT)
	{
		if (!shiftActive)
		{
			shiftActive = true;

			KeyboardButtonEvent event;
			event.button = Keyboard::LEFT_SHIFT;
			event.buttonState = Button::DOWN;

			Messages::send(Events::KEYBOARD_BUTTON, &event);
		}
	}
	else
	{
		if (shiftActive)
		{
			shiftActive = false;

			KeyboardButtonEvent event;
			event.button = Keyboard::LEFT_SHIFT;
			event.buttonState = Button::UP;

			Messages::send(Events::KEYBOARD_BUTTON, &event);
		}
	}
}

void fireKeyboardSpecialButtonDownEvent(const int key, const int x, const int y)
{
	KeyboardButtonEvent event = getKeyboardSpecialButtonEvent(key);
	event.buttonState = Button::DOWN;

	fireKeyboardModifierButtonEvent();
	Messages::send(Events::KEYBOARD_BUTTON, &event);
}

void fireKeyboardSpecialButtonUpEvent(const int key, const int x, const int y)
{
	KeyboardButtonEvent event = getKeyboardSpecialButtonEvent(key);
	event.buttonState = Button::UP;

	fireKeyboardModifierButtonEvent();
	Messages::send(Events::KEYBOARD_BUTTON, &event);
}

void fireMouseButtonEvent(const int button, const int state, const int x, const int y)
{
	MouseButtonEvent event;

	if (button == GLUT_MIDDLE_BUTTON)
	{
		event.button = Mouse::MIDDLE;
	}
	else if (button == GLUT_LEFT_BUTTON)
	{
		event.button = Mouse::LEFT;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		event.button = Mouse::RIGHT;
	}
	// Wheel reports as button 3 (up) and button 4 (down)
	else if (button == 3)
	{
		event.button = Mouse::WHEEL_UP;
	}
	else if (button == 4)
	{
		event.button = Mouse::WHEEL_DOWN;
	}

	if (state == GLUT_DOWN)
	{
		event.buttonState = Button::DOWN;
	}
	else
	{
		event.buttonState = Button::UP;
	}

	event.x = x;
	event.y = y;

	Messages::send(Events::MOUSE_BUTTON, &event);
}

void fireMouseMoveEvent(const int x, const int y)
{
	MouseMoveEvent event;
	event.x = x;
	event.y = y;

	Messages::send(Events::MOUSE_MOVE, &event);
}

KeyboardButtonEvent getKeyboardButtonEvent(const unsigned char key)
{
	KeyboardButtonEvent event;

	map<unsigned char, Keyboard::Button>::iterator buttonPair = freeGlutAsciiKeyboardButtonMap.find(key);
	if (buttonPair != freeGlutAsciiKeyboardButtonMap.end())
	{
		event.button = buttonPair->second;
	}

	event.character = key;

	return event;
}

KeyboardButtonEvent getKeyboardSpecialButtonEvent(const int key)
{
	KeyboardButtonEvent event;

	map<int, Keyboard::Button>::iterator buttonPair = freeGlutSpecialKeyboardButtonMap.find(key);
	if (buttonPair != freeGlutSpecialKeyboardButtonMap.end())
	{
		event.button = buttonPair->second;
	}

	event.character = key;

	return event;
}
