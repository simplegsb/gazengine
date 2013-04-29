#ifndef FREEGLUTINPUTEVENTS_H_
#define FREEGLUTINPUTEVENTS_H_

#include <gazengine/input/KeyboardButtonEvent.h>
#include <gazengine/input/MouseButtonEvent.h>
#include <gazengine/input/MouseMoveEvent.h>

void fireKeyboardButtonDownEvent(const unsigned char key, const int x, const int y);

void fireKeyboardButtonUpEvent(const unsigned char key, const int x, const int y);

void fireKeyboardModifierButtonEvent();

void fireKeyboardSpecialButtonDownEvent(const int key, const int x, const int y);

void fireKeyboardSpecialButtonUpEvent(const int key, const int x, const int y);

void fireMouseButtonEvent(const int button, const int state, const int x, const int y);

void fireMouseMoveEvent(const int x, const int y);

void fireMouseWheelEvent(const int x, const int y);

KeyboardButtonEvent getKeyboardButtonEvent(const unsigned char key);

KeyboardButtonEvent getKeyboardSpecialButtonEvent(const int key);

#endif /* FREEGLUTINPUTEVENTS_H_ */
