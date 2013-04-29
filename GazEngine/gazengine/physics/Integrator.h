#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include "SimpleBody.h"

class Integrator
{
	public:
		virtual ~Integrator()
		{
		}

		virtual void integrate(SimpleBody& body) = 0;
};

#endif /* INTEGRATOR_H_ */
