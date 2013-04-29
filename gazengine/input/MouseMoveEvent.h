#ifndef MOUSEMOVEEVENT_H_
#define MOUSEMOVEEVENT_H_

struct MouseMoveEvent
{
	MouseMoveEvent() :
		x(0), y(0)
	{
	}

	/**
	 * The location at which the event took place on the x axis.
	 */
	int x;

	/**
	 * The location at which the event took place on the y axis.
	 */
	int y;
};

#endif /* MOUSEMOVEEVENT_H_ */
