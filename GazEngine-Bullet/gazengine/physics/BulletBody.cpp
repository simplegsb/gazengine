#include <gazengine/model/Plane.h>
#include <gazengine/model/shape/Cube.h>
#include <gazengine/model/shape/Sphere.h>

#include "../math/BulletVector.h"
#include "BulletBody.h"

BulletBody::BulletBody(const Material& material, const Model* model, const Vector3& position) :
	body(NULL),
	bulletModel(NULL),
	linearAcceleration(0.0f, 0.0f, 0.0f),
	linearVelocity(0.0f, 0.0f, 0.0f),
	material(material),
	model(model),
	motionState(NULL),
	position(position)
{
	const Cube* cube = dynamic_cast<const Cube*>(model);
	if (cube != NULL)
	{
		bulletModel = new btBoxShape(btVector3(cube->getHalfEdgeLength(), cube->getHalfEdgeLength(),
			cube->getHalfEdgeLength()));
	}
	const Plane* plane = dynamic_cast<const Plane*>(model);
	if (plane != NULL)
	{
		bulletModel = new btStaticPlaneShape(BulletVector::toBtVector3(plane->getNormal()), 1.0f);
	}
	const Sphere* sphere = dynamic_cast<const Sphere*>(model);
	if (sphere != NULL)
	{
		bulletModel = new btSphereShape(sphere->getRadius());
	}

	bulletModel->calculateLocalInertia(0.0f, btVector3(0.0f, 0.0f, 0.0f));

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(BulletVector::toBtVector3(position));
	motionState = new btDefaultMotionState(transform);

	body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(0.0f, motionState, bulletModel));
	body->setFriction(material.friction);
	body->setRestitution(material.restitution);
	body->setRollingFriction(material.friction);
}

BulletBody::~BulletBody()
{
	if (body != NULL)
	{
		delete body;
	}

	if (bulletModel != NULL)
	{
		delete bulletModel;
	}

	if (motionState != NULL)
	{
		delete motionState;
	}
}

void BulletBody::applyForce(const Vector3& force, const Vector3& position)
{
	body->applyForce(BulletVector::toBtVector3(force), BulletVector::toBtVector3(position));
}

void BulletBody::clearForces()
{
	body->clearForces();
}

btRigidBody* BulletBody::getBody()
{
	return body;
}

const Vector3& BulletBody::getLinearAcceleration() const
{
	return linearAcceleration; // ???
}

const Vector3& BulletBody::getLinearVelocity() const
{
	linearVelocity = BulletVector::toVector3(body->getLinearVelocity());
	return linearVelocity;
}

float BulletBody::getMass() const
{
	return body->getInvMass();
}

const Body::Material& BulletBody::getMaterial() const
{
	return material;
}

const Model* BulletBody::getModel() const
{
	return model;
}

const Vector3& BulletBody::getPosition() const
{
	position = BulletVector::toVector3(body->getWorldTransform().getOrigin());
	return position;
}

bool BulletBody::isDynamic()
{
	return getMass() != 0.0f;
}

void BulletBody::setDynamic(bool dynamic)
{
	if (!dynamic)
	{
		setMass(0.0f);
	}
}

void BulletBody::setLinearVelocity(const Vector3& linearVelocity)
{
	body->setLinearVelocity(BulletVector::toBtVector3(linearVelocity));
}

void BulletBody::setMass(float mass)
{
	body->setMassProps(mass, body->getInvInertiaDiagLocal());
}

void BulletBody::setMaterial(const Material& material)
{
	this->material = material;

	body->setFriction(material.friction);
	body->setRestitution(material.restitution);
	body->setRollingFriction(material.friction);
}

void BulletBody::setNode(SimpleTree* node)
{
	body->setUserPointer(node);
}

void BulletBody::setPosition(const Vector3& position)
{
	body->getWorldTransform().setOrigin(BulletVector::toBtVector3(position));
}
