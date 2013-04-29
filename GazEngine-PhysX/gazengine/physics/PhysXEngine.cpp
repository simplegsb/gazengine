#include <gazengine/GazEngine.h>
#include <gazengine/graph/SimpleTree.h>

#include "../math/PhysXMatrix.h"
#include "../math/PhysXVector.h"
#include "PhysXEngine.h"

using namespace physx;
#if defined(DEBUG) || defined(_DEBUG)
using namespace PVD;
#endif

PhysXEngine::PhysXEngine(const Vector3& gravity, float fixedTimeStep) :
	allocator(),
	cooking(),
	cpuDispatcher(NULL),
	errorCallback(),
	fixedTimeStep(fixedTimeStep),
	foundation(NULL),
	gravity(gravity),
	physics(NULL),
	scene(NULL),
	simulationEventCallback(NULL),
	simulationFilterShader(PxDefaultSimulationFilterShader)
{
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);

#if defined(DEBUG) || defined(_DEBUG)
	PxProfileZoneManager& profileZoneManager =
		PxProfileZoneManager::createProfileZoneManager(foundation);
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, &profileZoneManager);

	if (physics->getPvdConnectionManager() != NULL)
	{
		PxInitExtensions(*physics);
		PvdConnection* debuggerConnection = PxVisualDebuggerExt::createConnection(physics->getPvdConnectionManager(),
			"localhost", 5425, 100, PxVisualDebuggerExt::getAllConnectionFlags());
		if (debuggerConnection != NULL)
		{
			debuggerConnection->release();
		}
	}
#else
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale());
#endif

	cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams());
}

void PhysXEngine::addEntity(Entity* entity)
{
	vector<PhysXBody*> entityBodies = entity->getComponents<PhysXBody>();
	for (unsigned int index = 0; index < entityBodies.size(); index++)
	{
		entityBodies[index]->getActor()->userData = entity;
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
		PxShape* shapes;
		static_cast<PxRigidBody*>(activeTransforms[index].actor)->getShapes(&shapes, 1);

		if (shapes->userData != NULL)
		{
			SimpleTree* node = static_cast<SimpleTree*>(shapes->userData);
			node->setTransformation(PhysXMatrix::toMatrix44(activeTransforms[index].actor2World));
		}
	}
}

void PhysXEngine::destroy()
{
	if (simulationEventCallback != NULL)
	{
		delete simulationEventCallback;
	}

	if (physics != NULL)
	{
		physics->release();
	}

	if (foundation != NULL)
	{
		foundation->release();
	}
}

PxCooking* PhysXEngine::getCooking()
{
	return cooking;
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
	sceneDesc.filterShader = simulationFilterShader;
	sceneDesc.simulationEventCallback = simulationEventCallback;

	scene = physics->createScene(sceneDesc);
}

void PhysXEngine::removeEntity(const Entity& entity)
{
	vector<PhysXBody*> entityBodies = entity.getComponents<PhysXBody>();
	for (unsigned int index = 0; index < entityBodies.size(); index++)
	{
		scene->removeActor(*entityBodies[index]->getActor());
	}
}

void PhysXEngine::setSimulationEventCallback(PxSimulationEventCallback* simulationEventCallback)
{
	this->simulationEventCallback = simulationEventCallback;
}

void PhysXEngine::setSimulationFilterShader(PxSimulationFilterShader simulationFilterShader)
{
	this->simulationFilterShader = simulationFilterShader;
}
