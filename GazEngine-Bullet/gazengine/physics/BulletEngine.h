#ifndef BULLETENGINE_H_
#define BULLETENGINE_H_

#include <gazengine/engine/Engine.h>

#include "BulletBody.h"

class BulletEngine : public Engine
{
	public:
		BulletEngine(const Vector3& gravity, float fixedTimeStep = 0.0f);

		void addEntity(Entity* entity);

		void advance();

		void destroy();

		void init();

		void removeEntity(const Entity& entity);

	private:
		std::vector<BulletBody*> bodies;

		btBroadphaseInterface* broadphase;

		btCollisionConfiguration* collisionConfiguration;

		btDispatcher* dispatcher;

		btConstraintSolver* solver;

		float fixedTimeStep;

		Vector3 gravity;

		btDynamicsWorld* world;
};

#endif /* BULLETENGINE_H_ */
