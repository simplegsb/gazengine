#ifndef PHYSICSFACTORY_H_
#define PHYSICSFACTORY_H_

#include "Body.h"

class PhysicsFactory
{
	public:
		virtual ~PhysicsFactory()
		{
		}

		virtual Body* createBody(Body::Material material, Model* model, Vector3 position, bool dynamic = true) = 0;

		static PhysicsFactory* getInstance();

		static void setInstance(PhysicsFactory* instance);

	private:
		static PhysicsFactory* instance;
};

#endif /* PHYSICSFACTORY_H_ */
