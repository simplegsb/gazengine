#include <gazengine/GazEngine.h>

#include "../math/BulletMatrix.h"
#include "../math/BulletVector.h"
#include "BulletEngine.h"

BulletEngine::BulletEngine(const Vector3& gravity, float fixedTimeStep) :
	broadphase(NULL),
	collisionConfiguration(NULL),
	dispatcher(NULL),
	fixedTimeStep(fixedTimeStep),
	gravity(gravity),
	solver(NULL),
	world(NULL)
{
}

void BulletEngine::addEntity(Entity* entity)
{
	vector<BulletBody*> entityBodies = entity->getComponents<BulletBody>();
	for (unsigned int index = 0; index < entityBodies.size(); index++)
	{
		world->addRigidBody(entityBodies[index]->getBody());
	}
}

void BulletEngine::advance()
{
	if (fixedTimeStep == 0.0f)
	{
		world->stepSimulation(GazEngine::getDeltaTime(), 10); // 10 is magic!
	}
	else
	{
		world->stepSimulation(fixedTimeStep, 1, fixedTimeStep);
	}

	btCollisionObjectArray& collisionObjects = world->getCollisionObjectArray();
	for (int index = 0; index < collisionObjects.size(); index++)
	{
		SimpleTree* node = static_cast<SimpleTree*>(collisionObjects[index]->getUserPointer());
		node->setTransformation(BulletMatrix::toMatrix44(collisionObjects[index]->getWorldTransform()));
	}
}

void BulletEngine::destroy()
{
	if (world != NULL)
	{
		delete world;
	}

	if (solver != NULL)
	{
		delete solver;
	}

	if (dispatcher != NULL)
	{
		delete dispatcher;
	}

	if (collisionConfiguration != NULL)
	{
		delete collisionConfiguration;
	}

	if (broadphase != NULL)
	{
		delete broadphase;
	}
}

void BulletEngine::init()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	world->setGravity(BulletVector::toBtVector3(gravity));
}

void BulletEngine::removeEntity(const Entity& entity)
{
	vector<BulletBody*> entityBodies = entity.getComponents<BulletBody>();
	for (unsigned int index = 0; index < entityBodies.size(); index++)
	{
		world->removeRigidBody(entityBodies[index]->getBody());
	}
}
