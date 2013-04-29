#ifndef PHYSXENGINE_H_
#define PHYSXENGINE_H_

#include <gazengine/engine/Engine.h>

#include "PhysXBody.h"

class PhysXEngine : public Engine
{
	public:
		PhysXEngine(const Vector3& gravity, float fixedTimeStep = 0.0f);

		~PhysXEngine();

		void addEntity(Entity* entity);

		void advance();

		void destroy();

		physx::PxPhysics* getPhysics();

		void init();

		void removeEntity(const Entity& entity);

	private:
		physx::PxDefaultAllocator allocator;

		std::vector<PhysXBody*> bodies;

		physx::PxDefaultCpuDispatcher* cpuDispatcher;

#if defined(DEBUG) || defined(_DEBUG)
		PVD::PvdConnection* debuggerConnection;
#endif

		physx::PxDefaultErrorCallback errorCallback;

		float fixedTimeStep;

		physx::PxFoundation* foundation;

		Vector3 gravity;

		physx::PxPhysics* physics;

		physx::PxScene* scene;
};

#endif /* PHYSXENGINE_H_ */
