#ifndef VERLETINTEGRATOR_H_
#define VERLETINTEGRATOR_H_

#include <map>

#include "Integrator.h"

class VerletIntegrator : public Integrator
{
	public:
		VerletIntegrator(float damping = 1.0f);

		void integrate(Body& body);

	private:
		float damping;

		std::map<Body*, Vector3> previousPositions;
};

#endif /* VERLETINTEGRATOR_H_ */
