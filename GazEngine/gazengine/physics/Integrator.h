#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include "Body.h"

class Integrator
{
	public:
		virtual ~Integrator()
		{
		}

		virtual void integrate(Body& body) = 0;
};

#endif /* INTEGRATOR_H_ */
