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
	cudaContextManager(NULL),
	errorCallback(),
	fixedTimeStep(fixedTimeStep),
	foundation(NULL),
	gravity(gravity),
	physics(NULL),
	profileZoneManager(NULL),
	scene(NULL),
	simulationEventCallback(NULL),
	simulationFilterShader(PxDefaultSimulationFilterShader)
{
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);
	profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(foundation);

#if defined(DEBUG) || defined(_DEBUG)
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, profileZoneManager);

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

	physics->getVisualDebugger()->setVisualizeConstraints(true);
	physics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlags::eTRANSMIT_CONTACTS, true);
#else
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale());
#endif

	cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams());

#ifdef PX_WINDOWS
    cudaContextManager = pxtask::createCudaContextManager(*foundation, pxtask::CudaContextManagerDesc(),
		profileZoneManager);
#endif
}

PhysXEngine::~PhysXEngine()
{
	if (cpuDispatcher != NULL)
	{
		cpuDispatcher->release();
	}

	if (cooking != NULL)
	{
		cooking->release();
	}

	if (physics != NULL)
	{
		physics->release();
	}

	if (cudaContextManager != NULL)
	{
		cudaContextManager->release();
	}

	if (profileZoneManager != NULL)
	{
		profileZoneManager->release();
	}

	if (foundation != NULL)
	{
		foundation->release();
	}
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
		PxShape* shape;
		static_cast<PxRigidBody*>(activeTransforms[index].actor)->getShapes(&shape, 1);
		SimpleTree* node = static_cast<SimpleTree*>(shape->userData);
		node->setTransformation(PhysXMatrix::toMatrix44(activeTransforms[index].actor2World));
	}
}

void PhysXEngine::destroy()
{
	if (scene != NULL)
	{
		scene->release();
	}

	if (simulationEventCallback != NULL)
	{
		delete simulationEventCallback;
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
	cpuDispatcher = PxDefaultCpuDispatcherCreate(1);

	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.cpuDispatcher = cpuDispatcher;
	sceneDesc.flags = PxSceneFlag::eENABLE_ACTIVETRANSFORMS | PxSceneFlag::eENABLE_SWEPT_INTEGRATION;
	if (cudaContextManager != NULL)
	{
		sceneDesc.gpuDispatcher = cudaContextManager->getGpuDispatcher();
	}
	sceneDesc.gravity = PhysXVector::toPxVec3(gravity);
	sceneDesc.filterShader = simulationFilterShader;
	sceneDesc.simulationEventCallback = simulationEventCallback;

	scene = physics->createScene(sceneDesc);

#if defined(DEBUG) || defined(_DEBUG)
	scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
	scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
#endif
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
