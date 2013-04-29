#ifndef PHYSXENGINE_H_
#define PHYSXENGINE_H_

#include <gazengine/engine/Engine.h>
#include <gazengine/math/Vector.h>

#include "PhysXBody.h"

class PhysXEngine : public Engine
{
	public:
		PhysXEngine(const Vector3& gravity, float fixedTimeStep);

		void addEntity(Entity* entity);

		void advance();

		void destroy();

		physx::PxCooking* getCooking();

		physx::PxPhysics* getPhysics();

		void init();

		void removeEntity(const Entity& entity);

		void setSimulationEventCallback(physx::PxSimulationEventCallback* simulationEventCallback);

		void setSimulationFilterShader(physx::PxSimulationFilterShader simulationFilterShader);

	private:
		physx::PxDefaultAllocator allocator;

		physx::PxCooking* cooking;

		physx::PxDefaultCpuDispatcher* cpuDispatcher;

		physx::PxDefaultErrorCallback errorCallback;

		float fixedTimeStep;

		physx::PxFoundation* foundation;

		Vector3 gravity;

		physx::PxPhysics* physics;

		physx::PxScene* scene;

		physx::PxSimulationEventCallback* simulationEventCallback;

		physx::PxSimulationFilterShader simulationFilterShader;
};

#endif /* PHYSXENGINE_H_ */
