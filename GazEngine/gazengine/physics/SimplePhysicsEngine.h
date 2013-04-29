#ifndef SIMPLEPHYSICSENGINE_H_
#define SIMPLEPHYSICSENGINE_H_

#include "../engine/Engine.h"
#include "Constraint.h"
#include "Integrator.h"

class SimplePhysicsEngine : public Engine
{
	public:
		SimplePhysicsEngine(const Vector3& gravity);

		~SimplePhysicsEngine();

		void addEntity(Entity* entity);

		void advance();

		void destroy();

		const Integrator* getIntegrator() const;

		void init();

		void removeEntity(const Entity& entity);

		void setIntegrator(Integrator* integrator);

	private:
		std::vector<SimpleBody*> bodies;

		std::vector<Constraint*> constraints;

		Vector3 gravity;

		Integrator* integrator;
};

#endif /* SIMPLEPHYSICSENGINE_H_ */
