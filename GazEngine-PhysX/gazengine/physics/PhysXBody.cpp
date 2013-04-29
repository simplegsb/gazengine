#include <gazengine/model/Plane.h>
#include <gazengine/model/shape/Cube.h>
#include <gazengine/model/shape/Sphere.h>

#include "../math/PhysXVector.h"
#include "PhysXBody.h"

using namespace physx;

PhysXBody::PhysXBody(PxPhysics& physics, const Material& material, const Model* model, const Vector3& position,
					 bool dynamic) :
	actor(NULL),
	dynamic(dynamic),
	linearAcceleration(0.0f, 0.0f, 0.0f),
	linearVelocity(0.0f, 0.0f, 0.0f),
	material(material),
	model(model),
	physxMaterial(NULL),
	physxModel(NULL),
	position(position)
{
	physxMaterial = physics.createMaterial(material.friction, material.friction, material.restitution);

	const Plane* plane = dynamic_cast<const Plane*>(model);
	if (plane != NULL)
	{
		actor = PxCreatePlane(physics, PxPlane(PhysXVector::toPxVec3(plane->getPositionOnPlane()),
			PhysXVector::toPxVec3(plane->getNormal())), *physxMaterial);
		return;
	}

	const Cube* cube = dynamic_cast<const Cube*>(model);
	if (cube != NULL)
	{
		physxModel = new PxBoxGeometry(cube->getHalfEdgeLength(), cube->getHalfEdgeLength(),
			cube->getHalfEdgeLength());
	}
	const Sphere* sphere = dynamic_cast<const Sphere*>(model);
	if (sphere != NULL)
	{
		physxModel = new PxSphereGeometry(sphere->getRadius());
	}

	if (dynamic)
	{
		actor = PxCreateDynamic(physics, PxTransform(PhysXVector::toPxVec3(position)), *physxModel, *physxMaterial,
			material.density);
	}
	else
	{
		actor = PxCreateStatic(physics, PxTransform(PhysXVector::toPxVec3(position)), *physxModel, *physxMaterial);
	}
}

PhysXBody::~PhysXBody()
{
	if (physxModel != NULL)
	{
		delete physxModel;
	}
}

void PhysXBody::applyForce(const Vector3& force, const Vector3&)
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		rigidBody->addForce(PhysXVector::toPxVec3(force));
	}
}

void PhysXBody::clearForces()
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		rigidBody->clearForce();
	}
}

PxActor* PhysXBody::getActor()
{
	return actor;
}

const Vector3& PhysXBody::getLinearAcceleration() const
{
	return linearAcceleration; // ???
}

const Vector3& PhysXBody::getLinearVelocity() const
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		linearVelocity = PhysXVector::toVector3(rigidBody->getLinearVelocity());
	}

	return linearVelocity;
}

float PhysXBody::getMass() const
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		return rigidBody->getMass();
	}

	return 0.0f;
}

const Body::Material& PhysXBody::getMaterial() const
{
	return material;
}

const Model* PhysXBody::getModel() const
{
	return model;
}

const Vector3& PhysXBody::getPosition() const
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		position = PhysXVector::toVector3(rigidBody->getGlobalPose().p);
	}

	return position;
}

bool PhysXBody::isDynamic()
{
	return dynamic;
}

void PhysXBody::setDynamic(bool)
{
	//assert(dynamic != this->dynamic && "PhysX bodys cannot be changed between dynamic and static...");
}

void PhysXBody::setLinearVelocity(const Vector3& linearVelocity)
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		rigidBody->setLinearVelocity(PhysXVector::toPxVec3(linearVelocity));
	}
}

void PhysXBody::setMass(float mass)
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		rigidBody->setMass(mass);
	}
}

void PhysXBody::setMaterial(const Material&)
{
}

void PhysXBody::setNode(SimpleTree* node)
{
	actor->userData = node;
}

void PhysXBody::setPosition(const Vector3& position)
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		PxTransform transform = rigidBody->getGlobalPose();
		transform.p = PhysXVector::toPxVec3(position);
		rigidBody->setGlobalPose(transform);
	}
}
