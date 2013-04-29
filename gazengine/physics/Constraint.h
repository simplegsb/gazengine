#ifndef CONSTRAINT_H_
#define CONSTRAINT_H_

#include "../Component.h"

class Constraint : public Component
{
	public:
		virtual void apply() = 0;
};

#endif /* CONSTRAINT_H_ */
