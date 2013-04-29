#include <algorithm>

#include <gazengine/GazEngine.h>
#include <gazengine/graph/SimpleTree.h>

#include "../math/PhysXMatrix.h"
#include "../math/PhysXVector.h"
#include "PhysXEngine.h"

using namespace physx;
using namespace PVD;

PhysXEngine::PhysXEngine(const Vector3& gravity, float fixedTimeStep) :
	allocator(),
	bodies(NULL),
	cpuDispatcher(NULL),
	errorCallback(),
	fixedTimeStep(fixedTimeStep),
	foundation(NULL),
	gravity(gravity),
	physics(NULL),
	scene(NULL)
{
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);

#if defined(DEBUG) || defined(_DEBUG)
	PxProfileZoneManager& profileZoneManager =
		PxProfileZoneManager::createProfileZoneManager(foundation);
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, &profileZoneManager);

	if (physics->getPvdConnectionManager() != NULL)
	{
		PxInitExtensions(*physics);
		debuggerConnection = PxVisualDebuggerExt::createConnection(physics->getPvdConnectionManager(), "localhost",
			5425, 100, PxVisualDebuggerExt::getAllConnectionFlags());
	}
#else
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), false, NULL);
#endif
}

PhysXEngine::~PhysXEngine()
{
#if defined(DEBUG) || defined(_DEBUG)
	if (debuggerConnection != NULL)
	{
		debuggerConnection->release();
	}
#endif
}

void PhysXEngine::addEntity(Entity* entity)
{
	vector<PhysXBody*> entityBodies = entity->getComponents<PhysXBody>();
	for (unsigned int index = 0; index < entityBodies.size(); index++)
	{
		bodies.push_back(entityBodies[index]);
		scene->addActor(*entityBodies[index]->getActor());
	}
}

void PhysXEngine::advance()
{
	if (fixedTimeStep == 0.0f)
	{
		scene->simulate(GazEngine::getDeltaTime());
	}
	else
	{
		scene->simulate(fixedTimeStep);
	}

	scene->fetchResults(true);

	PxU32 activeTransformCount;
	PxActiveTransform* activeTransforms = scene->getActiveTransforms(activeTransformCount);

	for (PxU32 index = 0; index < activeTransformCount; index++)
	{
		SimpleTree* node = static_cast<SimpleTree*>(activeTransforms[index].userData);
		node->setTransformation(PhysXMatrix::toMatrix44(activeTransforms[index].actor2World));
	}
}

void PhysXEngine::destroy()
{
	if (physics != NULL)
	{
		physics->release();
	}

	if (foundation != NULL)
	{
		foundation->release();
	}
}

PxPhysics* PhysXEngine::getPhysics()
{
	return physics;
}

void PhysXEngine::init()
{
	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	sceneDesc.cpuDispatcher = cpuDispatcher;
	sceneDesc.flags = PxSceneFlag::eENABLE_ACTIVETRANSFORMS;
	sceneDesc.gravity = PhysXVector::toPxVec3(gravity);
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;

	scene = physics->createScene(sceneDesc);
}

void PhysXEngine::removeEntity(const Entity& entity)
{
	vector<PhysXBody*> entityBodies = entity.getComponents<PhysXBody>();
	for (unsigned int index = 0; index < entityBodies.size(); index++)
	{
		bodies.erase(remove(bodies.begin(), bodies.end(), entityBodies[index]));
		scene->removeActor(*entityBodies[index]->getActor());
	}
}
